#include "enpch.h"
#include "RTPointLight.h"

#include "..//Utilities/ShadeRec.h"

namespace Engine {
	RTPointLight::RTPointLight()
		:m_Ls(1.0),
		m_Color(1.0),
		m_Location(0.0)
	{
	}
	RTPointLight::~RTPointLight()
	{
	}
	glm::vec3 RTPointLight::GetDirection(ShadeRec& sr)
	{
		return glm::normalize(m_Location - sr.local_hit_point);
	}

	glm::vec3 RTPointLight::L(ShadeRec& sr)
	{
		return m_Ls * m_Color;
	}
}


