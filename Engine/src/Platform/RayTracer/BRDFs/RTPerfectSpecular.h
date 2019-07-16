#pragma once

#include "RTBRDF.h"

#include "Engine/BRDF/PerfectSpecular.h"

namespace Engine {

	class RTPerfectSpecular : public PerfectSpecular
	{

	public:
		RTPerfectSpecular();

		~RTPerfectSpecular();

		virtual glm::vec3 f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const override;

		virtual glm::vec3 SampleF(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi) const override;

		virtual glm::vec3 Rho(const ShadeRec& sr, const glm::vec3& wo) const override;

		// Inherited via PerfectSpecular
		virtual void RenderInspectorInfo() override;
	};
}