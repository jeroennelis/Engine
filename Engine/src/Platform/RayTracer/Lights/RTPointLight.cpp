#include "enpch.h"
#include "RTPointLight.h"

#include "..//Utilities/ShadeRec.h"
#include "../World/World.h"

namespace Engine {
	RTPointLight::RTPointLight()
		:m_Location(0.0)
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

	bool RTPointLight::InShadow(const Ray & ray, const ShadeRec & sr) const
	{
		float t;
		int num_objects = sr.w.objects.size();
		float d = glm::distance(m_Location, ray.o);

		for (int j = 0; j < num_objects; j++)
			if (sr.w.objects[j]->ShadowHit(ray, t) && t < d)
				return true;

		return false;
	}
}


