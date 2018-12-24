#include "ParticleForceGenerator.h"
namespace physics
{
	void ParticleForceRegistry::Add(Particle * particle, ParticleForceGenerator * fg)
	{
		Registrations.push_back(ParticleForceRegistration{ particle, fg });
	}

	void ParticleForceRegistry::Remove(Particle * particle, ParticleForceGenerator * fg)
	{
		std::vector<ParticleForceRegistration>::iterator it = Registrations.begin();
		while (it != Registrations.end()) {
			if (it->Particle == particle && it->ForceGenerator == fg)
			{
				it = Registrations.erase(it);
				break;
			}

		}
	}

	void ParticleForceRegistry::Clear()
	{
		Registrations.clear();
	}

	void ParticleForceRegistry::UpdateForces(real duration)
	{
		for (ParticleForceRegistration& registration : Registrations)
			registration.ForceGenerator->UpdateForce(registration.Particle, duration);
	}

	ParticleGravity::ParticleGravity(const Vector3 & gravity)
		:m_Gravity(gravity)
	{
	}

	void ParticleGravity::UpdateForce(Particle * particle, real duration)
	{
		//make sure the particle does not have an infinite mass
		if (!particle->HasFiniteMass())
			return;

		//apply a mass-scaled force to the particle
		particle->AddForce(m_Gravity * particle->GetMass());
	}

	ParticleDrag::ParticleDrag(real k1, real k2)
		:m_K1(k1), m_K2(k2)
	{
	}

	void ParticleDrag::UpdateForce(Particle * particle, real duration)
	{
		Vector3 force;
		particle->GetVelocity(&force);

		//calculate the total drag coefficient
		real coefficient = force.Magnitude();
		coefficient = m_K1 * coefficient + m_K2 * coefficient * coefficient;

		//calculate and apply final force
		force.Normalize();
		force *= -coefficient;
		//TODO check if standing still
		particle->AddForce(force);
	}


	ParticleSpring::ParticleSpring(Particle * other, real springConstant, real restLength)
		:other(other), springConstant(springConstant), restLength(restLength)
	{
	}

	void ParticleSpring::UpdateForce(Particle * particle, real duration)
	{
		//Calculate the vector of the spring
		Vector3 force;
		particle->GetPosition(&force);
		force -= other->GetPosition();

		//Calculate the magnitude of the force
		real magnitude = force.Magnitude();
		magnitude = real_abs(magnitude - restLength) *springConstant;

		//calculate and apply final force
		force.Normalize();
		force *= -magnitude;
		particle->AddForce(force);
	}

	ParticleAnchoredSpring::ParticleAnchoredSpring(Vector3 * anchor, real springConstant, real restLength)
		:anchor(anchor), springConstant(springConstant), restLength(restLength)
	{
	}

	void ParticleAnchoredSpring::UpdateForce(Particle * particle, real duration)
	{
		// calculate the vector of the spring
		Vector3 force;
		particle->GetPosition(&force);
		force -= *anchor;

		// Calculate the magnitude of the force
		real magnitude = force.Magnitude();
		magnitude = (restLength - magnitude) * springConstant;

		// Calculate and apply final force
		force.Normalize();
		force *= magnitude;
		particle->AddForce(force);
	}

	ParticleBungee::ParticleBungee(Particle * other, real springConstant, real restLength)
		:other(other), springConstant(springConstant), restLength(restLength)
	{
	}
	void ParticleBungee::UpdateForce(Particle * particle, real duration)
	{
		// calculate the vector of the spring
		Vector3 force;
		particle->GetPosition(&force);
		force -= other->GetPosition();

		//	Check if the bungee is compressed
		real magnitude = force.Magnitude();
		if (magnitude <= restLength)
			return;
		
		// Calculate the magnitude of the force
		magnitude = springConstant * (restLength - magnitude);

		// Calculate the final force and apply it
		force.Normalize();
		force *= -magnitude;
		particle->AddForce(force);
	}

	ParticleBuoyency::ParticleBuoyency(real maxDepth, real volume, real waterHeight, real liquidDensity)
		:maxDepth(maxDepth), volume(volume), waterHeight(waterHeight), liquidDensity(liquidDensity)
	{
	}
	
	void ParticleBuoyency::UpdateForce(Particle * particle, real duration)
	{
		// Calculate submersion depth
		real depth = particle->GetPosition().Y;

		// check if out of the water
		if (depth >= waterHeight + maxDepth)
			return;
		Vector3 force(0, 0, 0);

		// check if at maximum depth
		if (depth <= waterHeight - maxDepth)
		{
			force.Y = liquidDensity * volume;
			particle->AddForce(force);
			return;
		}

		// else: partially submerged
		force.Y = liquidDensity * volume * (depth - maxDepth - waterHeight) / 2 * maxDepth;
		particle->AddForce(force);
			

	}

	ParticleFakeSpring::ParticleFakeSpring(Vector3 * anchor, real springConstant, real damping)
		:anchor(anchor), springConstant(springConstant), damping(damping)
	{
	}

	void ParticleFakeSpring::UpdateForce(Particle * particle, real duration)
	{
		// check that we do not have infinite mass
		if (!particle->HasFiniteMass())
			return;

		// calculate relative position of the particle to the anchor
		Vector3 position;
		particle->GetPosition(&position);
		position -= *anchor;

		//calculate the constants and check that they are in bounds
		real gamma = 0.5f * real_sqrt(4 * springConstant - damping * damping);
		if (gamma == 0.0f)
			return;
		Vector3 c = position * (damping / (2.0 * gamma)) + particle->GetVelocity() * (1.0f / gamma);

		//calculate target position
		Vector3 target = position * real_cos(gamma * duration) + c * real_sin(gamma * duration);
		target *= real_exp(-0.5f * duration * damping);

		// calculate the resulting acceleration (force)

		Vector3 acceleration = (target - position) * (1.0f / duration * duration) - particle->GetVelocity() * duration;
		particle->AddForce(acceleration * particle->GetMass());
	}
}

