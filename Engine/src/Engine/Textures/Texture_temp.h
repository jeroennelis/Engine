#pragma once

#include "Platform/RayTracer/Utilities/ShadeRec.h"

namespace Engine {

	class Texture_temp {
	public:
		virtual glm::vec3 GetColor(const ShadeRec& sr = ShadeRec()) const {return  glm::vec3(0.0,0.0,0.0 ); }

		virtual void RenderInspectorInfo() = 0;
	};
}