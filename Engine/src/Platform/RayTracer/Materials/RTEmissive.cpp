#include "enpch.h"
#include "RTEmissive.h"
#include "../Utilities\Constants.h"

namespace Engine {
	RTEmissive::RTEmissive()
		:RTMaterial()
	{
	}

	RTEmissive::~RTEmissive()
	{
	}

	glm::vec3 RTEmissive::GetLe(ShadeRec& sr) const
	{
		if (glm::dot(-sr.normal, sr.ray.d) > 0.0)
			return(m_Ls * m_Ce);
		else
			return black;
	}

	glm::vec3 RTEmissive::Shade(ShadeRec& sr)
	{
		if (glm::dot(-sr.normal, sr.ray.d) > 0.0)
			return(m_Ls * m_Ce);
		else
			return black;
	}

	glm::vec3 RTEmissive::ShadeAreaLight(ShadeRec& sr)
	{
		if (glm::dot(-sr.normal, sr.ray.d) > 0.0)
			return(m_Ls * m_Ce);
		else
			return black;
	}

}

