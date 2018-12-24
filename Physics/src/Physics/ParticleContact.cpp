#include "ParticleContact.h"

namespace physics {

	void ParticleContact::Resolve(real duration)
	{
		resolveVelocity(duration);
		resolveInterPenetration(duration);
	}

	real ParticleContact::CalculateSaperatingVelocity() const
	{
		Vector3 relativeVelocity = particle[0]->GetVelocity();
		if (particle[1])
			relativeVelocity -= particle[1]->GetVelocity();
		return relativeVelocity * contactNormal;
	}

	void ParticleContact::resolveVelocity(real duration)
	{
		// find the velocity in the direction of the contact
		real separatingVelocity = CalculateSaperatingVelocity();

		// check if it needs to be resolved
		if (separatingVelocity > 0)
			//contact is separating or stationary -> no impulse required
			return;

		// calculate the new separating velocity
		real newSeperatingVelocity = -separatingVelocity * restitution;

		real deltaVelocity = newSeperatingVelocity - separatingVelocity;

		// apply change in velocity to each object in proportion to their inverse mass
		real totalInverseMass = particle[0]->GetInverseMass();
		if (particle[1])
			totalInverseMass += particle[1]->GetInverseMass();

		// if all particles have infinite mass, impulses have no effect
		if (totalInverseMass <= 0)
			return;

		// calculate the impulse to apply
		real impulse = deltaVelocity / totalInverseMass;

		// calculate the amount of impulse per unit of inverse mass
		Vector3 impulsePerIMass = contactNormal * impulse;

		//apply impulses, in the direction of the contact,
		//in proportion of the inverse mass
		particle[0]->SetVelocity(particle[0]->GetVelocity() + impulsePerIMass * particle[0]->GetInverseMass());
		if(particle[1])
			//particle 1 goes in opposite direction of particle 0
			particle[1]->SetVelocity(particle[1]->GetVelocity() + impulsePerIMass * -particle[1]->GetInverseMass());
	}

	void ParticleContact::resolveInterPenetration(real duration)
	{
		// no interpenetration -> return
		if (penetration <= 0)
			return;

		//movement of each object is based on their inverse mass, so total that
		real totalInverseMass = particle[0]->GetInverseMass();
		if (particle[1])
			totalInverseMass += particle[1]->GetInverseMass();

		//if total inverse mass is infinite -> return
		if (totalInverseMass <= 0)
			return;

		//find amount of penetration resolution per unit of mass
		Vector3 movePerIMass = contactNormal * (penetration / totalInverseMass);

		//calculate amount of movement
		particleMovement[0] = movePerIMass * particle[0]->GetInverseMass();
		if (particle[1])
			particleMovement[1] = movePerIMass * -particle[1]->GetInverseMass();
		else
			particleMovement[1].Clear();

		//apply penetration resolution
		particle[0]->SetPosition(particle[0]->GetPosition() + particleMovement[0]);
		if (particle[1])
			particle[1]->SetPosition(particle[1]->GetPosition() + particleMovement[1]);
	}


	ParticleContactResolver::ParticleContactResolver(unsigned iterations)
		:iterations(iterations)
	{}

	void ParticleContactResolver::ResolveContacts(ParticleContact* contactArray, unsigned numContacts, real duration)
	{
		unsigned i;

		iterationsUsed = 0;
		while (iterationsUsed < iterations)
		{
			// Find contact with the largest closing velocity
			real max = REAL_MAX;
			unsigned maxIndex = numContacts;
			for (i = 0; i < numContacts; i++)
			{
				real sepVel = contactArray[i].CalculateSaperatingVelocity();
				if (sepVel < max && (sepVel < 0 || contactArray[i].penetration >0))
				{
					max = sepVel;
					maxIndex = i;
				}
			}

			//check if needs resolving
			if (maxIndex == numContacts) 
				break;

			//resolve contact
			contactArray[maxIndex].Resolve(duration);
			iterationsUsed++;
		}
	}
}