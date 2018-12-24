#include "ParticleWorld.h"

namespace physics {

	ParticleWorld::ParticleWorld(unsigned maxContacts, unsigned iterations)
		:resolver(iterations), maxContacts(maxContacts)
	{
		contacts = new ParticleContact[maxContacts];
		calculateIterations = (iterations == 0);
	}

	ParticleWorld::~ParticleWorld()
	{
		delete[] contacts;
	}

	unsigned ParticleWorld::GenerateContacts()
	{
		unsigned limit = maxContacts;
		ParticleContact *nextContact = contacts;
		
		for (ContactGenerators::iterator g = contactGenerators.begin(); g != contactGenerators.end(); g++)
		{
			unsigned used = (*g)->AddContact(nextContact, limit);
			limit -= used;
			nextContact += used;

			//ran out of contacts to fill -> missing contacts
			if (limit <= 0)
				break;
		}

		//return nr of contacts used
		return maxContacts - limit;
	}

	void ParticleWorld::Integrate(real duration)
	{
		for (Particle * particle: particles)
		{
			particle->Integrate(duration);
		}
	}

	void ParticleWorld::runPhysics(real duration)
	{
		//apply force generators
		registry.UpdateForces(duration);

		//integrate objects
		Integrate(duration);

		//generate contacts
		unsigned usedContacts = GenerateContacts();

		if (usedContacts)
		{
			if (calculateIterations)
				resolver.SetIterations(usedContacts * 2);
			resolver.ResolveContacts(contacts, usedContacts, duration);
		}
	}
}