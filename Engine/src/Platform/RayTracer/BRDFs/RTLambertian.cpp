#include "enpch.h"
#include "RTLambertian.h"
#include "..//Textures/RTConstantColor.h"

namespace Engine{
	RTLambertian::RTLambertian()
		:Lambertian()
	{
	}
	RTLambertian::~RTLambertian()
	{
	}
	glm::vec3 RTLambertian::f(const ShadeRec & sr, const glm::vec3 & wi, const glm::vec3 & wo) const
	{
		return (m_Kd * (float)invPI * m_Cd->GetColor(sr) );
	}

	glm::vec3 RTLambertian::SampleF(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi) const
	{
		return glm::vec3();
	}

	glm::vec3 RTLambertian::Rho(const ShadeRec & sr, const glm::vec3 & wo) const
	{
		return (m_Kd * (m_Cd)->GetColor(sr));
	}
	void RTLambertian::RenderInspectorInfo()
	{
	}
}
