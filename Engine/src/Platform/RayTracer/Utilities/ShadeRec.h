#pragma once

#include "Ray.h"
#include "..//Materials/RTMaterial.h"

namespace Engine {


	// this file contains the declaration of the class ShadeRec

	class World;	// only need a forward class declaration as the World data member is a reference



	class ShadeRec {
	public:

		bool		hit_an_object;		// did the ray hit an object?
		RTMaterial*	material_ptr;		// nearest object's material
		glm::vec3	hit_point;			// world coordinates of hit point
		glm::vec3	local_hit_point;	// for attaching textures to objects 
		glm::vec3	normal;				// normal at hit point
		glm::vec3	color;				// used in Chapter 3 only
		Ray			ray;				// for specular highlights
		int			depth;				// recursion depth
		glm::vec3	dir;				// for area lights
		float		t;					// ray parameter
		float		u;					// texture coordinate
		float		v;					// texture coordinate
		World&		w;					// world reference for shading

		ShadeRec(World& wr);				// constructor

		ShadeRec(const ShadeRec& sr);		// copy constructor
	};
}