#include "enpch.h"
#include "GlossySpecular.h"

namespace Engine {

	GlossySpecular::GlossySpecular()
		:m_Ks(1.0),
		m_Cs(glm::vec3(1.0)),
		m_Exp(1.0)
	{
	}

	GlossySpecular::~GlossySpecular()
	{
	}

	glm::vec3 GlossySpecular::f(const ShadeRec & sr, const glm::vec3 & wi, const glm::vec3 & wo) const
	{
		glm::vec3 L(0.0);
		float nDotWi = glm::dot(sr.normal, wi);
		glm::vec3 r(-wi + 2.0f * sr.normal * nDotWi);
		float rDotWo = glm::dot(r, wo);

		if (rDotWo > 0.0)
			L = glm::vec3(m_Ks) * pow(rDotWo, m_Exp);
		return L;
	}

	glm::vec3 GlossySpecular::SampleF(const ShadeRec & sr, glm::vec3 & wi, const glm::vec3 & wo) const
	{
		return glm::vec3();
	}

	glm::vec3 GlossySpecular::Rho(const ShadeRec & sr, const glm::vec3 & wo) const
	{
		return glm::vec3();
	}
}