#include "enpch.h"
#include "RTGlossySpecular.h"

namespace Engine {

	RTGlossySpecular::RTGlossySpecular()
		:RTBRDF(),
		GlossySpecular()
	{
	}

	RTGlossySpecular::~RTGlossySpecular()
	{
	}

	glm::vec3 RTGlossySpecular::f(const ShadeRec & sr, const glm::vec3 & wi, const glm::vec3 & wo) const
	{
		glm::vec3 L(0.0);
		float nDotWi = glm::dot(sr.normal, wi);
		glm::vec3 r(-wi + 2.0f * sr.normal * nDotWi);
		float rDotWo = glm::dot(r, wo);

		if (rDotWo > 0.0)
			L = glm::vec3(m_Ks) * pow(rDotWo, m_Exp);
		return L;
	}

	glm::vec3 RTGlossySpecular::SampleF(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi) const
	{
		return glm::vec3();
	}

	glm::vec3 RTGlossySpecular::Rho(const ShadeRec & sr, const glm::vec3 & wo) const
	{
		return glm::vec3();
	}

	RTBRDF* RTGlossySpecular::clone(void) const
	{
		return (new RTGlossySpecular(*this));
	}
}