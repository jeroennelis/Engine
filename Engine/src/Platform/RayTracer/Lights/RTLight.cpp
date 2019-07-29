#include "enpch.h"
#include "RTLight.h"

namespace Engine {

	RTLight::RTLight()
		:m_Shadows(true),
		m_Ls(1.0),
		m_Color(0.9)
	{
	}

	RTLight::~RTLight()
	{
	}

	bool RTLight::InShadow(const Ray & ray, const ShadeRec & sr) const
	{
		return false;
	}

	float RTLight::G(const ShadeRec& sr) const
	{
		return 1.0f;
	}

	float RTLight::Pdf(ShadeRec& sr) const
	{
		return 1.0f;
	}
}

