#pragma once

#include "Tracer.h"

namespace Engine {

	class AreaLighting : public Tracer
	{
	public :
		AreaLighting(World* _world);
		~AreaLighting();

		virtual glm::vec3 trace_ray(const Ray ray, const int depth) const;

	};
}
