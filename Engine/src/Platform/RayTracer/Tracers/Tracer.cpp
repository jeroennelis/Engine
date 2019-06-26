#include "enpch.h"

#include "Tracer.h"
#include "../World/World.h"

namespace Engine {
	// -------------------------------------------------------------------- default constructor

	Tracer::Tracer(void)
		: world_ptr(NULL)
	{}


	// -------------------------------------------------------------------- constructor

	Tracer::Tracer(World* _worldPtr)
		: world_ptr(_worldPtr)
	{}



	// -------------------------------------------------------------------- destructor

	Tracer::~Tracer(void) {
		if (world_ptr)
			world_ptr = NULL;
	}


	// -------------------------------------------------------------------- trace_ray

	glm::vec3
		Tracer::trace_ray(const Ray& ray) const 
	{
		EN_CORE_ASSERT(false, "not implemented yet");
		return black;
	}


	// -------------------------------------------------------------------- trace_ray

	glm::vec3
		Tracer::trace_ray(const Ray ray, const int depth) const 
	{
		EN_CORE_ASSERT(false, "not implemented yet");
		return black;
	}


	// -------------------------------------------------------------------- trace_ray

	glm::vec3 Tracer::trace_ray(const Ray ray, float& tmin, const int depth)
	{
		EN_CORE_ASSERT(false, "not implemented yet");
		return black;
	}
}