#pragma once
#include "Tracer.h"
#include "..//Utilities/ShadeRec.h"
#include "../World/World.h"

namespace Engine {
	class MultipleObjects :
		public Tracer
	{
	public:
		MultipleObjects(void);
		MultipleObjects(World* _world_ptr);
		~MultipleObjects();

		glm::vec3 trace_ray(const Ray& ray) const;
	};
}