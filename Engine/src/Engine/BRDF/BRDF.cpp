#include "enpch.h"
#include "BRDF.h"

namespace Engine {

	glm::vec3 BRDF::f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const
	{
		EN_CORE_ASSERT(false, "not implemented");
		return glm::vec3();
	}

	glm::vec3 BRDF::SampleF(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi) const
	{
		EN_CORE_ASSERT(false, "not implemented");
		return glm::vec3();
	}
	glm::vec3 BRDF::Rho(const ShadeRec& sr, const glm::vec3& wo) const
	{
		EN_CORE_ASSERT(false, "not implemented");
		return glm::vec3();
	}

	void BRDF::Bind()
	{
		EN_CORE_ASSERT(false, "not implemented");
	}
}


