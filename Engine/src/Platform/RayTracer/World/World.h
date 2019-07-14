#pragma once
#include "ViewPlane.h"
#include "../GeometricObjects//Sphere.h"
#include "../GeometricObjects/Plane.h"
#include "../Samplers/Jittered.h"
#include "../Samplers/NRooks.h"
#include "../Samplers/MultiJittered.h"
#include "Platform/RayTracer/Tracers/Tracer.h"
#include "Platform/RayTracer/Tracers/MultipleObjects.h"

#include "Engine/image.h"
#include <stdio.h>

#include "../Cameras/RTPinhole.h"
#include "../Lights/RTLight.h"
#include "..//Lights/RTAmbient.h"

#include "Engine/Logic/Scene.h"

namespace Engine{

	class World
	{
	public:
		ViewPlane	vp;
		RTCamera*	camera_ptr;
		Tracer*		tracer_ptr;
		glm::vec3	background_color;
		RTLight*	ambient_ptr;
		std::vector<GeometricObject*>	objects;
		std::vector<RTLight*> lights;

		Image*		image;
		
		


		World(void);
		~World(void);

		void build(Scene& scene);

		void add_object(GeometricObject* object_ptr);

		void AddLight(RTLight* light);

		inline void SetAmbientLight(RTLight* ambient) { ambient_ptr = ambient; }

		ShadeRec hit_objects(const Ray& ray);

		void render_scene(std::string& filename) const;

		void render_perspective(std::string& filename) const;

		void set_pixel(const int row, const int column, const glm::vec3& pixelColor) const;
		
		inline void SetCamera(RTCamera* camera) { camera_ptr = camera; }

		inline void SaveImage(const std::string& path) { image->saveImage(path); }


		glm::vec3 MaxToOne(const glm::vec3& c) const;

		glm::vec3 ClampToColor(const glm::vec3& rawColor) const;
	};

	inline void World::add_object(GeometricObject* object_ptr)
	{
		objects.push_back(object_ptr);
	}

	inline void World::AddLight(RTLight* light)
	{
		lights.push_back(light);
	}
}





