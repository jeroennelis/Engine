#pragma once

#include "BRDF.h"

namespace Engine {

	class GlossySpecular : public BRDF
	{
	public:
		GlossySpecular();
		~GlossySpecular();

		virtual glm::vec3 f(const ShadeRec & sr, const glm::vec3 & wi, const glm::vec3 & wo) const override;
		virtual glm::vec3 SampleF(const ShadeRec & sr, glm::vec3 & wi, const glm::vec3 & wo) const override;
		virtual glm::vec3 Rho(const ShadeRec & sr, const glm::vec3 & wo) const override;

		inline void SetKs(const float ks) { m_Ks = ks; }
		inline void SetCs(const glm::vec3& cs) { m_Cs = cs; }
		inline void SetExp(const float exp) { m_Exp = exp; }

	private:
		float m_Ks;
		glm::vec3 m_Cs;
		float m_Exp;
	};
}