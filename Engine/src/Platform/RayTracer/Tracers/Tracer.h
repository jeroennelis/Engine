// This is the declaration of the base class Tracer
// The tracer classes have no copy constructor, assignment operator. or clone function because 
// of the world pointer, which should not be assigned or copy constructed
// See comments in the World.h file.

#pragma once

#include "../Utilities/Constants.h"
#include "../Utilities/Ray.h"

namespace Engine {
	class World;

	class Tracer {
	public:

		Tracer(void);

		Tracer(World* _world_ptr);

		virtual
			~Tracer(void);

		virtual glm::vec3
			trace_ray(const Ray& ray) const;

		virtual glm::vec3
			trace_ray(const Ray ray, const int depth) const;

	protected:

		World* world_ptr;
	};
}