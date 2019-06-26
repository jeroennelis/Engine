#include "enpch.h"
#include "RayCast.h"

#include "../Utilities/ShadeRec.h"
#include "../World/World.h"


namespace Engine {

	RayCast::RayCast(World* world)
		:Tracer(world)
	{
	}

	RayCast::~RayCast()
	{
	}

	glm::vec3 RayCast::trace_ray(const Ray ray, const int depth) const
	{
		ShadeRec sr(world_ptr->hit_objects(ray));

		if (sr.hit_an_object)
		{
			sr.ray = ray;
			return(sr.material_ptr->Shade(sr));
		}
		else
			return world_ptr->background_color;
	}
}


