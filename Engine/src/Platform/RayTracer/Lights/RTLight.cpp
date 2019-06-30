#include "enpch.h"
#include "RTLight.h"

namespace Engine {

	RTLight::RTLight()
		:m_Shadows(true),
		m_Ls(1.0),
		m_Color(1.0)
	{
	}

	RTLight::~RTLight()
	{
	}

	bool RTLight::InShadow(const Ray & ray, const ShadeRec & sr) const
	{
		return false;
	}
}

