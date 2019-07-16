#pragma once

#include "Platform/RayTracer/Utilities/ShadeRec.h"

namespace Engine {


	class BRDF
	{
	public:
		virtual glm::vec3 f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const;

		virtual glm::vec3 SampleF(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi) const;

		virtual glm::vec3 Rho(const ShadeRec& sr, const glm::vec3& wo) const;

		virtual void RenderInspectorInfo() = 0;

		virtual void Bind();
	};
}
