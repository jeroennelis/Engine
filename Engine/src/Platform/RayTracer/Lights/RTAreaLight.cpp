#include "enpch.h"
#include "RTAreaLight.h"

#include "..//World/World.h"
#include "..//Utilities/ShadeRec.h"

namespace Engine {

	RTAreaLight::RTAreaLight()
		:RTLight(),
		m_Object(nullptr),
		m_Material(nullptr)
	{
	}

	RTAreaLight::~RTAreaLight()
	{
	}
	glm::vec3 RTAreaLight::GetDirection(ShadeRec& sr)
	{
		m_SamplePoint = m_Object->Sample();
		m_LightNormal = m_Object->GetNormal(m_SamplePoint);
		m_Wi = m_SamplePoint - sr.local_hit_point;
		m_Wi = glm::normalize(m_Wi);
		return m_Wi;
	}
	bool RTAreaLight::InShadow(const Ray& ray, const ShadeRec& sr) const
	{
		float t;
		int numObjects = sr.w.objects.size();
		float ts = glm::dot((m_SamplePoint - ray.o) , ray.d);

		for (int j = 0; j < numObjects; j++)
			if (sr.w.objects[j]->ShadowHit(ray, t) && t < ts)
				return true;
		return false;
	}
	glm::vec3 RTAreaLight::L(ShadeRec& sr)
	{
		float nDotD = glm::dot(-m_LightNormal, m_Wi);

		if (nDotD < 0.0)
			return m_Material->GetLe(sr);
		return black;
	}
	float RTAreaLight::G(const ShadeRec& sr) const
	{
		float nDotD = glm::dot(-m_LightNormal, m_Wi);
		float d2 = pow(glm::distance(m_SamplePoint, sr.local_hit_point), 2);

		return nDotD / d2;
	}
	float RTAreaLight::Pdf(ShadeRec& sr) const
	{
		return m_Object->Pdf(sr);
	}
}

