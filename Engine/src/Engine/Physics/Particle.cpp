#include "enpch.h"
#include "Particle.h"
namespace physics
{ 
	Particle::Particle(glm::vec3 * position)
		:Position(position), Velocity(0, 0, 0), Acceleration(0, 0, 0), forceAccumulator(0, 0, 0), InverseMass(0), Damping(1.0)
	{
	}

	Particle::Particle(glm::vec3 * position, glm::vec3 & velocity)
		: Position(position), Velocity(velocity), Acceleration(0, 0, 0), forceAccumulator(0, 0, 0), InverseMass(0), Damping(1.0)
	{
	}

	Particle::Particle(glm::vec3 * position, glm::vec3 & velocity, glm::vec3 & acceleration)
		: Position(position), Velocity(velocity), Acceleration(acceleration), forceAccumulator(0, 0, 0), InverseMass(0), Damping(1.0)
	{
	}

	void Particle::SetMass(const real mass)
	{
		assert(mass != 0);
		InverseMass = ((real)1.0) / mass;
	}

	real Particle::GetMass() const
	{
		if (InverseMass == 0)
			return REAL_MAX;
		return ((real)1.0) / InverseMass;
	}

	void Particle::SetInverseMass(const real inverseMass)
	{
		InverseMass = inverseMass;
	}

	real Particle::GetInverseMass() const
	{
		return InverseMass;
	}

	bool Particle::HasFiniteMass() const
	{
		return InverseMass >= 0.0f;
	}

	void Particle::SetDamping(const real damping)
	{
		Damping = damping;
	}

	real Particle::GetDamping() const
	{
		return Damping;
	}

	void Particle::SetPosition(const glm::vec3 & position)
	{
		*Position = position;
	}

	void Particle::SetPosition(const real x, const real y, const real z)
	{
		Position->x = x;
		Position->y = y;
		Position->z = z;
	}

	void Particle::GetPosition(glm::vec3 * position) const
	{
		position = Position;
	}

	glm::vec3 Particle::GetPosition() const
	{
		return *Position;
	}

	void Particle::SetVelocity(const glm::vec3 & velocity)
	{
		Velocity = velocity;
	}

	void Particle::SetVelocity(const real x, const real y, const real z)
	{
		Velocity.x = x;
		Velocity.y = y;
		Velocity.z = z;
	}

	void Particle::GetVelocity(glm::vec3 * velocity) const
	{
		*velocity = Velocity;
	}

	glm::vec3 Particle::GetVelocity() const
	{
		return Velocity;
	}

	void Particle::SetAcceleration(const glm::vec3 & acceleration)
	{
		Acceleration = acceleration;
	}

	void Particle::SetAcceleration(const real x, const real y, const real z)
	{
		Acceleration.x = x;
		Acceleration.y = y;
		Acceleration.z = z;
	}

	void Particle::GetAcceleration(glm::vec3 * acceleration) const
	{
		*acceleration = Acceleration;
	}

	glm::vec3 Particle::GetAcceleration() const
	{
		return Acceleration;
	}

	void Particle::Integrate(real duration)
	{

		//particles with infinite mass aren't interpolated
		if (InverseMass <= 0.0)
			return;

		assert(duration > 0.0);

		//update position
		*Position += Velocity * duration;


		//calculate acceleration from all applied forces
		glm::vec3 resultingAcceleration = Acceleration;
		resultingAcceleration += forceAccumulator * InverseMass;

		//upadte linear velocity from the acceleration
		Velocity += resultingAcceleration * duration;

		//add drag
		Velocity *= real_pow(Damping, duration);

		//clear all forces
		ClearAccumulator();
	}

	void Particle::AddForce(const glm::vec3 & force)
	{
		forceAccumulator += force;
	}

	void Particle::ClearAccumulator()
	{
		forceAccumulator = glm::vec3(0,0,0);
	}

}
