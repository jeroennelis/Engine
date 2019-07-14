#include "enpch.h"
#include "RTPerfectSpecular.h"

namespace Engine {
	RTPerfectSpecular::RTPerfectSpecular()
		:RTBRDF(),
		PerfectSpecular()
	{
	}

	RTPerfectSpecular::~RTPerfectSpecular()
	{
	}

	RTPerfectSpecular* RTPerfectSpecular::clone() const
	{
		return nullptr;
	}

	glm::vec3 RTPerfectSpecular::f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const
	{
		return black;
	}

	glm::vec3 RTPerfectSpecular::SampleF(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi) const
	{
		float ndotwo = glm::dot(sr.normal, wo);
		wi = -wo + 2.0f * sr.normal * ndotwo;
		return (m_Kr * m_Cr->GetColor(sr) / fabs(glm::dot(sr.normal, wi)));
	}

	glm::vec3 RTPerfectSpecular::Rho(const ShadeRec& sr, const glm::vec3& wo) const
	{
		return black;
	}
}


