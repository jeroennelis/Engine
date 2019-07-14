#pragma once

#include "Tracer.h"

namespace Engine {

	class Whitted : public Tracer
	{

	public: 
		Whitted();

		Whitted(World* worldPtr);

		virtual ~Whitted();

		virtual glm::vec3 trace_ray(const Ray ray, const int depth) const override;
	};
}