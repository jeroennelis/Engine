#include "enpch.h"
#include "RTAmbientOccluder.h"

#include "../Utilities/ShadeRec.h"
#include "../World/World.h"
namespace Engine {

	RTAmbientOccluder::RTAmbientOccluder()
		:m_U(), m_V(), m_W(),
		m_Sampler(nullptr),
		m_MinAmount(0.0)
	{
	}

	RTAmbientOccluder::~RTAmbientOccluder()
	{
	}

	void RTAmbientOccluder::SetSampler(Sampler * sampler)
	{
		if (m_Sampler)
		{
			delete m_Sampler;
			m_Sampler = nullptr;
		}
		m_Sampler = sampler;
		sampler->map_samples_hemisphere(1);
	}

	glm::vec3 RTAmbientOccluder::GetDirection(ShadeRec & sr)
	{
		glm::vec3 sp = m_Sampler->SampleHemisphere();
		return (sp.x * m_U + sp.y * m_V + sp.z * m_W);
	}

	bool RTAmbientOccluder::InShadow(const Ray & ray, const ShadeRec & sr) const
	{
		float t;
		int num_objects = sr.w.objects.size();

		for (int j = 0; j < num_objects; j++)
			if (sr.w.objects[j]->ShadowHit(ray, t))
				return true;
		return false;
	}

	glm::vec3 RTAmbientOccluder::L(ShadeRec & sr)
	{
		m_W = sr.normal;
		m_V = glm::cross(m_W, glm::vec3(0.0072, 1.0, 0.0034)); //jitter to prevent completely horizontal
		m_V = glm::normalize(m_V);
		m_U = glm::cross(m_V, m_W);

		Ray shadowRay;
		shadowRay.o = sr.local_hit_point;
		shadowRay.d = GetDirection(sr);

		if (InShadow(shadowRay, sr))
			return (m_MinAmount * m_Ls * m_Color);
		else
			return (m_Ls * m_Color);

	}
}