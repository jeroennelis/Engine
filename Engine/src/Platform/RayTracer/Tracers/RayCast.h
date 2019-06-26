#pragma once

#include "Tracer.h"

namespace Engine {

	class RayCast : public Tracer {
	public:
		RayCast(World* world);
		~RayCast();

		virtual glm::vec3 trace_ray(const Ray ray, const int depth) const;


	};
}