#include "enpch.h"
#include "AreaLighting.h"

#include "..//Utilities/ShadeRec.h"
#include "..//World/World.h"

namespace Engine {

	AreaLighting::AreaLighting(World* world)
		:Tracer(world)
	{
	}
	AreaLighting::~AreaLighting()
	{
	}

	glm::vec3 AreaLighting::trace_ray(const Ray ray, const int depth) const
	{
		ShadeRec sr(world_ptr->hit_objects(ray));

		if (sr.hit_an_object)
		{
			sr.ray = ray;
			return(sr.material_ptr->ShadeAreaLight(sr));
		}
		else
			return(world_ptr->background_color);
	}
}

