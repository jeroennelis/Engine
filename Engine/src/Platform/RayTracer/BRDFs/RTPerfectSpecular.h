#pragma once

#include "RTBRDF.h"

#include "Engine/BRDF/PerfectSpecular.h"

namespace Engine {

	class RTPerfectSpecular : public RTBRDF, public PerfectSpecular
	{

	public:
		RTPerfectSpecular();

		~RTPerfectSpecular();

		virtual RTPerfectSpecular* clone() const override;

		virtual glm::vec3 f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const override;

		virtual glm::vec3 SampleF(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi) const override;

		virtual glm::vec3 Rho(const ShadeRec& sr, const glm::vec3& wo) const override;
	};
}