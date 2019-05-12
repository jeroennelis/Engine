#pragma once
#include <assert.h>
#include "Precision.h"

namespace physics {

	class  Particle
	{
	protected:
		/**
		* Linear position of the particle in world space
		**/
		glm::vec3 * Position;

		/**
		* Linear velocity of the particle in world space
		**/
		glm::vec3 Velocity;


		/**
		* acceleration of the particle
		**/
		glm::vec3 Acceleration;

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

		/**
		* holds the total force that needs to be applied the next frame
		**/
		glm::vec3 forceAccumulator;

	public:

		Particle(glm::vec3* position);

		Particle(glm::vec3* position, glm::vec3& velocity);

		Particle(glm::vec3* position, glm::vec3& velocity, glm::vec3& acceleration);

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

		void SetPosition(const glm::vec3 & position);
		void SetPosition(const real x, const real y, const real z);
		void GetPosition(glm::vec3 *position) const;
		glm::vec3 GetPosition() const;

		void SetVelocity(const glm::vec3 &velocity);
		void SetVelocity(const real x, const real y, const real z);
		void GetVelocity(glm::vec3 *velocity) const;
		glm::vec3 GetVelocity() const;

		void SetAcceleration(const glm::vec3 &acceleration);
		void SetAcceleration(const real x, const real y, const real z);
		void GetAcceleration(glm::vec3 *acceleration) const;
		glm::vec3 GetAcceleration() const;

		/**
		* integrates the particle forward in time by a given amount
		**/
		void Integrate(real duration);

		/**
		* adds a ginven force to this particle to be applied the next iteration
		**/
		void AddForce(const glm::vec3& force);

		/**
		* Clears the applied force to the particle,
		* is called automatically after each integration step
		**/

		void ClearAccumulator();
	};

}

