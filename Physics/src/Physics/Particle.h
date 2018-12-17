#pragma once
#include "core.h"
#include "Utils.h"
#include <assert.h>

namespace physics {

	class PHYSICS_API Particle
	{
	protected:
		/**
		* Linear position of the particle in world space
		**/
		Vector3 Position;

		/**
		* Linear velocity of the particle in world space
		**/
		Vector3 Velocity;


		/**
		* acceleration of the particle
		**/
		Vector3 Acceleration;

		/**
		* amount of damping applied to linear motion.
		* damping removes energy added through numerical instability of the integrator
		**/
		real Damping;

		/**
		* inverse of the mass
		* makes is easier for integration
		* object with infinite mass will heve a zero inverse mass
		**/
		real InverseMass;
	public:
		Particle();

		Particle(Vector3& position);

		Particle(Vector3& position, Vector3& velocity);

		Particle(Vector3& position, Vector3& velocity, Vector3& acceleration);

		/**
		* sets the mass of the particle
		* @param mass is the new mass of the particle. This may not be zero
		* small masses might cause unstable rigid bodies
		**/
		void SetMass(const real mass);

		/**
		* calculate and return the mass of the particle
		* in case of an infinite mass, returns the maximum real number
		**/
		real GetMass()const;

		/**
		* Sets the inverse mass of the particle
		*
		* @param inverseMass is the new inverse mass for the particle. 
		* It may be zero for infinite mass (== unmovable)
		**/
		void SetInverseMass(const real inverseMass);
		
		/**
		* @return the current inverse mass of the particle
		**/
		real GetInverseMass() const;

		/**
		* returns true if the particle has an infinite mass
		**/
		bool HasFiniteMass() const;

		/**
		* sets the damping of the particle
		**/
		void SetDamping(const real damping);

		/**
		* gets the damping value
		**/
		real GetDamping() const;

		void SetPosition(const Vector3 &position);
		void SetPosition(const real x, const real y, const real z);
		void GetPosition(Vector3 *position) const;
		Vector3 GetPosition() const;

		void SetVelocity(const Vector3 &velocity);
		void SetVelocity(const real x, const real y, const real z);
		void GetVelocity(Vector3 *velocity) const;
		Vector3 GetVelocity() const;

		void SetAcceleration(const Vector3 &acceleration);
		void SetAcceleration(const real x, const real y, const real z);
		void GetAcceleration(Vector3 *acceleration) const;
		Vector3 GetAcceleration() const;

		/**
		* integrates the particle forward in time by a given amount
		**/
		void Integrate(real duration);

		/**
		* adds a ginven force to this particle to be applied the next iteration
		**/
		void AddForce(const Vector3& force);


	private:
		/**
		* holds the total force that needs to be applied the next frame
		**/
		Vector3 forceAccumulator;

		/**
		* Clears the applied force to the particle,
		* is called automatically after each integration step
		**/
		void ClearAccumulator();
	};

}

