#pragma once

#include "BRDF.h"

namespace Engine {

	class Lambertian : public BRDF
	{
	public:

		Lambertian();
		~Lambertian();
	
		virtual glm::vec3 f(const ShadeRec & sr, const glm::vec3 & wi, const glm::vec3 & wo) const override;

		virtual glm::vec3 SampleF(const ShadeRec & sr, glm::vec3 & wi, const glm::vec3 & wo) const override;

		virtual glm::vec3 Rho(const ShadeRec & sr, const glm::vec3 & wo) const override;

		inline void SetReflectionCoefficient(const float kd) { m_Kd = kd; }
		inline void SetColor(const glm::vec3& cd) { m_Cd = cd; }

	private:
		float m_Kd;
		glm::vec3 m_Cd;
	};
}
