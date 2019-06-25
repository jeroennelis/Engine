#include "enpch.h"
#include "Lambertian.h"

namespace Engine{
	Lambertian::Lambertian()
	{
	}
	Lambertian::~Lambertian()
	{
	}
	glm::vec3 Lambertian::f(const ShadeRec & sr, const glm::vec3 & wi, const glm::vec3 & wo) const
	{
		return (m_Kd * (float)invPI * m_Cd );
	}

	glm::vec3 Lambertian::SampleF(const ShadeRec & sr, glm::vec3 & wi, const glm::vec3 & wo) const
	{
		return glm::vec3();
	}

	glm::vec3 Lambertian::Rho(const ShadeRec & sr, const glm::vec3 & wo) const
	{
		return (m_Kd * m_Cd);
	}
}
