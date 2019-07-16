#pragma once

#include "Platform/RayTracer/Utilities/ShadeRec.h"

namespace Engine {

	class Texture {
	public:
		virtual glm::vec3 GetColor(const ShadeRec& sr = ShadeRec() ) const = 0;

		virtual void RenderInspectorInfo() = 0;
	};
}