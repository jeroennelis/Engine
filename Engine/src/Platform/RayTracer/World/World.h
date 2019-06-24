#pragma once
#include "ViewPlane.h"
#include "../GeometricObjects//Sphere.h"
#include "../GeometricObjects/Plane.h"
#include "../Samplers/Jittered.h"
#include "../Samplers/NRooks.h"
#include "../Samplers/MultiJittered.h"
#include "Platform/RayTracer/Tracers/Tracer.h"
#include "Platform/RayTracer/Tracers/MultipleObjects.h"

#include "../image.h"
#include <stdio.h>

#include "../Cameras/RTPinhole.h"

namespace Engine{

	class World
	{
	public:
		ViewPlane	vp;
		glm::vec3	background_color;
		Sphere		sphere;
		Tracer*		tracer_ptr;
		Image*		image;
		RTCamera*	camera_ptr;

		std::vector<GeometricObject*>	objects;

		World(void);
		~World(void);

		void build(void);

		void add_object(GeometricObject* object_ptr);

		ShadeRec hit_bare_bones_objects(const Ray& ray);

		void render_scene(std::string& filename) const;

		void render_perspective(std::string& filename) const;

		void set_pixel(const int row, const int column, const glm::vec3& pixelColor) const;
		
		inline void SetCamera(RTCamera* camera) { camera_ptr = camera; }
	};

	inline void World::add_object(GeometricObject* object_ptr)
	{
		objects.push_back(object_ptr);
	}
}





