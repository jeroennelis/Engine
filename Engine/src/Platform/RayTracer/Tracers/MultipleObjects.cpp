#include "enpch.h"

#include "MultipleObjects.h"

namespace Engine {
	MultipleObjects::MultipleObjects()
	{
	}

	MultipleObjects::MultipleObjects(World* _world_ptr)
		:Tracer(_world_ptr)
	{
	}


	MultipleObjects::~MultipleObjects()
	{
	}

	glm::vec3 MultipleObjects::trace_ray(const Ray& ray) const
	{
		ShadeRec sr(world_ptr->hit_objects(ray));

		if (sr.hit_an_object)
			return (sr.color);
		else
			return world_ptr->background_color;
	}
}