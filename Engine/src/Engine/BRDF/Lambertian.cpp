#include "enpch.h"
#include "Lambertian.h"

namespace Engine {

	Lambertian::Lambertian()
		:BRDF(),
		m_Kd(0.0),
		m_Cd()
	{
	}

	/*glm::vec3 Lambertian::f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const
	{
		EN_CORE_ASSERT(false, "not implemented");
		return glm::vec3();
	}

	glm::vec3 Lambertian::SampleF(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi) const
	{
		EN_CORE_ASSERT(false, "not implemented");
		return glm::vec3();
	}

	glm::vec3 Lambertian::Rho(const ShadeRec& sr, const glm::vec3& wo) const
	{
		EN_CORE_ASSERT(false, "not implemented");
		return glm::vec3();
	}*/
}


