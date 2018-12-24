#include "ParticleLinks.h"

namespace physics {

	real ParticleLink::currentLenght() const
	{
		Vector3 relativePos = particle[0]->GetPosition() - particle[1]->GetPosition();
		return relativePos.Magnitude();
	}

	unsigned ParticleCable::AddContact(ParticleContact* contact, unsigned limit) const
	{
		// find lenght of the cable
		real length = currentLenght();

		// check if overextended
		if (length < maxLength)
			return 0;

		contact->particle[0] = particle[0];
		contact->particle[1] = particle[1];

		//calculate normal
		Vector3 normal = particle[1]->GetPosition() - particle[0]->GetPosition();
		normal.Normalize();
		contact->contactNormal = normal;

		contact->penetration = length - maxLength;
		contact->restitution = restitution;
		return 1;
	}
	unsigned ParticleRod::AddContact(ParticleContact * contact, unsigned limit) const
	{
		// find lenght of the cable
		real currentLen = currentLenght();

		// check if overextending
		if (currentLen == length)
			return 0;

		contact->particle[0] = particle[0];
		contact->particle[1] = particle[1];

		//calculate normal
		Vector3 normal = particle[1]->GetPosition() - particle[0]->GetPosition();
		normal.Normalize();

		//contact normal depends on whether is't extending or compressing
		if (currentLen > length)
		{
			contact->contactNormal = normal;
			contact->penetration = currentLen - length;
		}
		else
		{
			contact->contactNormal = normal * -1;
			contact->penetration = length - currentLen;
		}

		// always 0 restitution -> no bounciness in rod
		contact->restitution = 0;

		return 1;
	}
}