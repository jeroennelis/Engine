#pragma once
#include <vector>
#include "Particle.h"


namespace  physics
{
	/**
	* a force generator can add a force to one or more particles
	**/
	class ParticleForceGenerator
	{
	public:

		/**
		* this function needs to be overloaded in the implementation of the interface
		* to update the force applied to the particle
		**/
		virtual void UpdateForce(Particle *particle, real duration) = 0;
	};

	/**
	* hollds all the force generators and the particles they are applied to
	**/
	class ParticleForceRegistry
	{

	protected:

		/**
		* keeps track of a force and the particle that it applies to
		**/
		struct ParticleForceRegistration
		{
			Particle *Particle;
			ParticleForceGenerator *ForceGenerator;
		};

		std::vector<ParticleForceRegistration> Registrations;

	public:

		/**
		* registers the given force generator to apply to the given particle
		**/
		void Add(Particle* particle, ParticleForceGenerator *fg);

		/**
		* removes the given registry pair from the registry
		* if the pair does not exist, there will be no effect
		**/
		void Remove(Particle* particle, ParticleForceGenerator *fg);

		/**
		* clears the registry
		* the particles and the force generators will not be deleted
		**/
		void Clear();

		/**
		* calls the update methods from all the force generators
		**/
		void UpdateForces(real duration);

	};

	/**
	* implementation of ForceGenerator that creates and applies a gravitational force on a particle
	* one instance can be used for multiple particles
	**/
	class ParticleGravity : public ParticleForceGenerator
	{
		/**
		* holds the acceleration generated by gravity
		**/
		glm::vec3 m_Gravity;

	public:

		/**
		* creates the generator with a given gravity
		**/
		ParticleGravity(const glm::vec3 &gravity);

		/**
		* applies the gracitational pull to the particle for the specified duration
		* Inherited via ParticleForceGenerator
		**/
		virtual void UpdateForce(Particle * particle, real duration) override;
	};

	/**
	* implementation of ForceGenerator that creates and applies a drag force on a particle
	* one instance can be used for multiple particles
	**/
	class ParticleDrag : public ParticleForceGenerator
	{
		/**
		* holds the velocity drag coefficent
		**/
		real m_K1;

		/**
		* holds the velocity squared coefficient
		**/
		real m_K2;

	public:
		/**
		* creates the generator with given coefficients
		**/ 
		ParticleDrag(real k1, real k2);

		/**
		* applies the drag force to the particle for the specified duration
		* Inherited via ParticleForceGenerator
		**/
		virtual void UpdateForce(Particle * particle, real duration) override;

	};

	/**
	* implementation of ForceGenerator that creates and applies a spring force to a particle
	**/
	class ParticleSpring : public ParticleForceGenerator
	{
		/**
		* holds the particle on the other side of the spring
		**/
		Particle *other;

		/**
		* holds the spring constant
		**/
		real springConstant;

		/**
		* holds the rest length of the spring
		**/
		real restLength;

	public:
		/**
		* creates a particle spring generator with the given parameters
		**/
		ParticleSpring(Particle *other, real springConstant, real restLength);

		/**
		* applies the spring force to the particle for the specified duration
		* Inherited via ParticleForceGenerator
		**/
		virtual void UpdateForce(Particle * particle, real duration) override;
	};

	/**
	* implementation of ForceGenerator that creates and applies a spring force to a particle,
	* one end is attached to a fixed point in space
	**/
	class ParticleAnchoredSpring : public ParticleForceGenerator
	{

	protected:
		/**
		* location of the enchored end of the spring
		**/
		glm::vec3 *anchor;

		/**
		* spring constant
		**/
		real springConstant;

		/**
		* rest lenght of the spring
		**/
		real restLength;

	public:
		/**
		* creates a particle spring generator with the given parameters
		**/
		ParticleAnchoredSpring(glm::vec3 *anchor, real springConstant, real restLength);

		/**
		* applies the spring force to the particle for the specified duration
		* Inherited via ParticleForceGenerator
		**/
		virtual void UpdateForce(Particle * particle, real duration) override;
	};

	/**
	*	implementation of forcegenerator that creates and applies a spring force to a particle,
	*	only when extende
	**/
	class ParticleBungee : ParticleForceGenerator
	{
		/**
		* holds the particle on the other side of the spring
		**/
		Particle *other;

		/**
		* holds the spring constant
		**/
		real springConstant;

		/**
		* holds the rest length of the spring
		**/
		real restLength;

	public:
		ParticleBungee(Particle* other, real springConstant, real restLenght);

		virtual void UpdateForce(Particle* particle, real duration) override;
	};

	/**
	*	implementation of forcegenerator that aplies a buoyancy force 
	*	for a plane of liquid parallel to the xz plane
	**/
	class ParticleBuoyency : public ParticleForceGenerator
	{
		/**
		*	maximum subersion depth of the object
		*	before generating the maximum buoyency force
		**/
		real maxDepth;

		/**
		*	volume of the object
		**/
		real volume;

		/**
		*	height of the water plane above y = 0.
		*	the plane is parallel to the xz plane.
		**/
		real waterHeight;

		/**
		*	denistiy of the liquid.
		*	reference: 1m� water -> 1000kg
		**/
		real liquidDensity;

	public:

		ParticleBuoyency(real maxDepth, real volume, real waterHeight, real liquidDensity = 1000.0f);

		virtual void UpdateForce(Particle* particle, real duration) override;
	};

	/**
	*	implementation of forcegenerator that applies a fake stif spring force 
	*	one end is attached to a fixed point in space
	**/
	class ParticleFakeSpring : public ParticleForceGenerator
	{

		/**
		*	Location of the anchored end of the spring
		**/
		glm::vec3 *anchor;

		/**
		*	spring constant
		**/
		real springConstant;
	
		/**
		*	dampning on oscillation of spring
		**/
		real damping;

	public:
		
		ParticleFakeSpring(glm::vec3* anchor, real springConstant, real damping);

		virtual void UpdateForce(Particle* particle, real duration) override;
	};

}



