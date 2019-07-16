#pragma once

#include "BRDF.h"
#include "Engine/Textures/Texture.h"

namespace Engine
{

	class Lambertian : public BRDF
	{

	public:
		Lambertian();

		/*virtual glm::vec3 f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const override;

		virtual glm::vec3 SampleF(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi) const override;

		virtual glm::vec3 Rho(const ShadeRec& sr, const glm::vec3& wo) const override;*/

		inline void SetKd(const float kd) { m_Kd = kd; }
		inline void SetCd(Texture* cd) { m_Cd = cd; }
		inline void SetKa(const float ka) { m_Kd = ka; }

		inline float GetKd() { return m_Kd; }
		inline Texture* GetCd() { return m_Cd; }

		virtual void RenderInspectorInfo() override = 0;


	protected:
		float m_Kd;
		Texture* m_Cd;
	};
}
