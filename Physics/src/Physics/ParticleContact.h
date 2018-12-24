#pragma once

#include "Particle.h"
#include "core.h"


namespace physics {

	/**
	*	a contact represent two objects in contact (two particles)
	*	Resolving a contact removes their interpenetration
	*	and applies sufficient impulse to keep them apart
	*	colliding bodies may remound
	*
	*	the contact has no callable functions, it just holds contact details
	*	contacts are resolved using the particle contact resolver class
	**/
	class PHYSICS_API ParticleContact
	{
		friend class ParticleContactResolver;

	public:
		// holds particles that are involved in the constact
		// second can be NULL for contacts with scenery
		Particle* particle[2];

		// holds the normal restitution coefficient at the contact
		real restitution;

		// holds the direction of te constact in world coordinates
		Vector3 contactNormal;

		// holds depth of penetration at the contact
		real penetration;

		// Holds the amount each particle is moved by during interpenetration resolution
		 
		Vector3 particleMovement[2];

	protected:
		//resolves this contact for both velocity and interpenetration
		void Resolve(real duration);

		//calculates the seperating velocity at this contact
		real CalculateSaperatingVelocity() const;

	private:
		//handles the ompulse calculations for this collision
		void resolveVelocity(real duration);

		// handles interpenetration resolution for this contact
		void resolveInterPenetration(real duration);
	};


	/**
	*	contact resolution routine for particle contacts.
	*	resolver instance can be shared for the entire simulation
	**/
	class PHYSICS_API ParticleContactResolver
	{
	protected:
		// # allowed iterations
		unsigned iterations;

		//performance tracking value
		// actual # iterations used
		unsigned iterationsUsed;

	public:
		ParticleContactResolver(unsigned iterations);

		/**
		*	sets # iterations that can be used
		**/
		inline void SetIterations(const unsigned iterations) { this->iterations = iterations; }

		/**
		*	resolves a set of particle contacts for both penetration and velocity
		**/
		void ResolveContacts(ParticleContact* contactArray, unsigned numContacts, real duration);
	};

	/**
	 * This is the basic polymorphic interface for contact generators
	 * applying to particles.
	 */
	class PHYSICS_API ParticleContactGenerator
	{
	public:
		/**
		 * Fills the given contact structure with the generated
		 * contact. The contact pointer should point to the first
		 * available contact in a contact array, where limit is the
		 * maximum number of contacts in the array that can be written
		 * to. The method returns the number of contacts that have
		 * been written.
		 */
		virtual unsigned AddContact(ParticleContact *contact, unsigned limit) const = 0;
	};
}
