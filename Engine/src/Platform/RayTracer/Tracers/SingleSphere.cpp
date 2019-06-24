#include "enpch.h"

#include "SingleSphere.h"


namespace Engine {
	SingleSphere::SingleSphere()
		:Tracer()
	{

	}

	SingleSphere::SingleSphere(World* _world_ptr)
		: Tracer(_world_ptr)
	{
	}


	SingleSphere::~SingleSphere()
	{
	}

	glm::vec3 SingleSphere::trace_ray(const Ray& ray) const
	{
		ShadeRec sr(*world_ptr);
		double t;
		if (world_ptr->sphere.hit(ray, t, sr))
			return (red);
		else
			return (black);
	}
}