#pragma once
#include "Tracer.h"
#include "../Utilities/ShadeRec.h"
#include "../World/World.h"

namespace Engine{
	class SingleSphere :
		public Tracer
	{
	public:
		SingleSphere(void);

		SingleSphere(World* _world_ptr);

		~SingleSphere();

		glm::vec3 trace_ray(const Ray& ray) const;
	};
}