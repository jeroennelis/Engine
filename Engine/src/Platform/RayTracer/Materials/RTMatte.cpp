#include "enpch.h"
#include "RTMatte.h"

namespace Engine {

	RTMatte::RTMatte()
		:RTMaterial(),
		m_AmbientBRDF(new Lambertian),
		m_DiffuseBRDF(new Lambertian)
	{
	}

	RTMatte::~RTMatte()
	{
	}

	void RTMatte::SetKa(const float ka)
	{
		m_AmbientBRDF->SetReflectionCoefficient(ka);
	}

	void RTMatte::SetKd(const float kd)
	{
		m_DiffuseBRDF->SetReflectionCoefficient(kd);
	}

	void RTMatte::SetCd(const glm::vec3& c)
	{
		m_AmbientBRDF->SetColor(c);
		m_DiffuseBRDF->SetColor(c);
	}

	glm::vec3 RTMatte::Shade(ShadeRec& sr)
	{
		glm::vec3 wo = -sr.ray.d;
		glm::vec3 L = m_AmbientBRDF->Rho(sr, wo) * sr.w.ambient_ptr->L(sr);
		int numLights = sr.w.lights.size();

		for (int j = 0; j < numLights; j++)
		{
			glm::vec3 wi = sr.w.lights[j]->GetDirection(sr);
			float ndotwi = glm::dot(sr.normal, wi);

			if (ndotwi > 0.0)
			{
				bool in_shadow = false;

				if (sr.w.lights[j]->CastsShadows())
				{
					Ray shadowRay(sr.local_hit_point, wi);
					in_shadow = sr.w.lights[j]->InShadow(shadowRay, sr);
				}

				if(!in_shadow)
					L += m_DiffuseBRDF->f(sr, wo, wi) * sr.w.lights[j]->L(sr) * ndotwi;
			}
				
		}

		return L;
	}
}


