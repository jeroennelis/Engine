#pragma once

#include "Platform/RayTracer/Utilities/ShadeRec.h"

namespace Engine {

	class Texture {
	public:
		virtual glm::vec3 GetColor(const ShadeRec& sr) const = 0;
	};
}