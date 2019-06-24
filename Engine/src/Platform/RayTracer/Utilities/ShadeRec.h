#pragma once

namespace Engine {


	// this file contains the declaration of the class ShadeRec

	class World;	// only need a forward class declaration as the World data member is a reference



	class ShadeRec {
	public:

		bool				hit_an_object;		// did the ray hit an object?
		glm::vec3			local_hit_point;	// world coordinates of hit point 
		glm::vec3			normal;				// normal at hit point
		glm::vec3			color;				// used in Chapter 3 only
		World& w;					// world reference for shading

		ShadeRec(World& wr);				// constructor

		ShadeRec(const ShadeRec& sr);		// copy constructor
	};
}