#pragma once

#include "Physics/ParticleContact.h"


namespace physics {

	/**
	*	links will connect two particles, generating a cointact if they violate the constraints of their link
	*	used as base class for cables, rods and springs with a limit to their extension.
	**/
	class PHYSICS_API ParticleLink : public ParticleContactGenerator
	{
	public:
		/**
		*	holds pair of particles that are connected
		**/
		Particle* particle[2];

	protected:
		/**
		*	return current length of the link
		**/
		real currentLenght() const;

	public:
		/**
		*	generates the contacts to keep this link from being violated
		*	only generates a single contact
		*	pointer is to a single element
		*	limit is assumed to be at least 1
		* 
		**/
		virtual unsigned AddContact(ParticleContact* contact, unsigned limit) const = 0;
	};

	
	/**
	*	a cable links a pair of particles, generating a contact if they stray too far apart
	**/
	class PHYSICS_API ParticleCable : public ParticleLink
	{
	public:
		/**
		*	maximum lenght of the cable
		**/
		real maxLength;

		/**
		*	holds restitution (bounciness) to the cable
		**/
		real restitution;

	public:
		/**
		*	fills the given contact structure with the contact needed to keep the cable from overextending
		**/
		virtual unsigned AddContact(ParticleContact* contact, unsigned limit) const;
	};


	/**
	*	a rod links a pair of particles, generating a contact if they stray too far apart or too close
	**/
	class PHYSICS_API ParticleRod : public ParticleLink
	{
	public:
		/**
		*	maximum lenght of the cable
		**/
		real length;

	public:
		/**
		*	fills the given contact structure with the contact needed to keep the rod from extending or compressing
		**/
		virtual unsigned AddContact(ParticleContact* contact, unsigned limit) const;
	};
}