#pragma once

#include "RTBRDF.h"
#include "Engine/BRDF/GlossySpecular.h"

namespace Engine {

	class RTGlossySpecular : public RTBRDF, public GlossySpecular
	{
	public:
		RTGlossySpecular();
		~RTGlossySpecular();

		virtual glm::vec3 f(const ShadeRec & sr, const glm::vec3 & wi, const glm::vec3 & wo) const override;
		virtual glm::vec3 SampleF(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi) const override;
		virtual glm::vec3 Rho(const ShadeRec & sr, const glm::vec3 & wo) const override;

		
		// Inherited via BRDF
		virtual RTBRDF* clone(void) const override;
	};
}