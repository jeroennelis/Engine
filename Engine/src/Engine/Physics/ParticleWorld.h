#pragma once

#include "Particle.h"
#include "ParticleForceGenerator.h"
#include "ParticleContact.h"
#include <iostream>
#include <vector>

namespace physics {

	/**
	 *	keeps track of all paricles and make it possible to update them
	 */
	class ParticleWorld
	{
	public:
		typedef std::vector<Particle*> Particles;
		typedef std::vector<ParticleContactGenerator*> ContactGenerators;

	protected:
		/**
		 *	holds all particles
		 */
		Particles particles;

		/**
		 * True if the world should calculate the number of iterations
		 * to give the contact resolver at each frame.
		 */
		bool calculateIterations;

		/**
		 *	holds force generators for the particles in the world
		 */
		ParticleForceRegistry registry;

		/**
		 *	holds resolver for contacts
		 */
		ParticleContactResolver resolver;

		/**
		 *	contact generators
		 */
		ContactGenerators contactGenerators;

		/**
		 *	list of contacts
		 */
		ParticleContact* contacts;

		/**
		 *	holds maximum nr of contacts allowed (size of the size of contacts array)
		 */
		unsigned maxContacts;

	public:
		/**
		 *	creates a new particle simulator that can handle up to a given number of contacts per frame
		 *	optional: nr of contact-resolution iterations, if not provided, it will be twice the nr of contacts
		 */
		ParticleWorld(unsigned maxContacts, unsigned iterations = 0);

		~ParticleWorld();
		
		/**
		 *	calls each of the registered contact generators to report their contacts.
		 *	returns the nr of generated contacts
		 */
		unsigned GenerateContacts();

		/**
		 *	integrates all the particles in the world forward in time by the given duration
		 */
		void Integrate(real duration);

		/**
		 *	processes all the physics for the particle world
		 **/
		void runPhysics(real duration);

		/**
		 *	initializes the world for simulation. 
		 *	called every frame
		 *	clears force accumulators 
		 *	after calling, particles have their forces for the frame added
		 */
		void StartFrame();

		/**
		 *  Returns the list of particles.
		 */
		inline Particles& getParticles() { return particles; }

		/**
		 * Returns the list of contact generators.
		 */
		inline ContactGenerators& getContactGenerators() { return contactGenerators; }

		/**
		 * Returns the force registry.
		 */
		inline ParticleForceRegistry& getForceRegistry() { return registry; }

	};
}
