#include "enpch.h"
#include "Whitted.h"

#include "..//World/World.h"

namespace Engine {

	Whitted::Whitted()
		:Tracer()
	{
	}

	Whitted::Whitted(World* worldPtr)
		:Tracer(worldPtr)
	{
	}

	Whitted::~Whitted()
	{
	}

	glm::vec3 Whitted::trace_ray(const Ray ray, const int depth) const
	{
		if (depth > world_ptr->vp.max_depth)
			return black;
		else
		{
			ShadeRec sr(world_ptr->hit_objects(ray));

			if (sr.hit_an_object)
			{
				sr.depth = depth;
				sr.ray = ray;

				return sr.material_ptr->Shade(sr);
			}
			else
				return world_ptr->background_color;
		}
		return glm::vec3();
	}
}