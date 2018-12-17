#include "Particle.h"
namespace physics
{ 
	Particle::Particle()
	{
	}

	Particle::Particle(Vector3 & position)
		:Position(position), InverseMass(0), Damping(1.0)
	{
	}

	Particle::Particle(Vector3 & position, Vector3 & velocity)
		: Position(position), Velocity(velocity), InverseMass(0), Damping(1.0)
	{
	}

	Particle::Particle(Vector3 & position, Vector3 & velocity, Vector3 & acceleration)
		: Position(position), Velocity(velocity), Acceleration(acceleration), InverseMass(0), Damping(1.0)
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

	void Particle::SetPosition(const Vector3 & position)
	{
		Position = position;
	}

	void Particle::SetPosition(const real x, const real y, const real z)
	{
		Position.X = x;
		Position.Y = y;
		Position.Z = z;
	}

	void Particle::GetPosition(Vector3 * position) const
	{
		*position = Position;
	}

	Vector3 Particle::GetPosition() const
	{
		return Position;
	}

	void Particle::SetVelocity(const Vector3 & velocity)
	{
		Velocity = velocity;
	}

	void Particle::SetVelocity(const real x, const real y, const real z)
	{
		Velocity.X = x;
		Velocity.Y = y;
		Velocity.Z = z;
	}

	void Particle::GetVelocity(Vector3 * velocity) const
	{
		*velocity = Velocity;
	}

	Vector3 Particle::GetVelocity() const
	{
		return Velocity;
	}

	void Particle::SetAcceleration(const Vector3 & acceleration)
	{
		Acceleration = acceleration;
	}

	void Particle::SetAcceleration(const real x, const real y, const real z)
	{
		Acceleration.X = x;
		Acceleration.Y = y;
		Acceleration.Z = z;
	}

	void Particle::GetAcceleration(Vector3 * acceleration) const
	{
		*acceleration = Acceleration;
	}

	Vector3 Particle::GetAcceleration() const
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
		Position.AddScaledVector(Velocity, duration);
		std::cout << "new position: " << Position << std::endl;


		//calculate acceleration from all applied forces
		Vector3 resultingAcceleration = Acceleration;
		resultingAcceleration.AddScaledVector(forceAccumulator, InverseMass);

		//upadte linear velocity from the acceleration
		Velocity.AddScaledVector(resultingAcceleration, duration);

		//add drag
		Velocity *= real_pow(Damping, duration);

		//clear all forces
		ClearAccumulator();
	}

	void Particle::AddForce(const Vector3 & force)
	{
		forceAccumulator += force;
	}

	void Particle::ClearAccumulator()
	{
		forceAccumulator.Clear();
	}

}
