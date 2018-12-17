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
}

