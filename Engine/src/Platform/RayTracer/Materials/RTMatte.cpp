#include "enpch.h"
#include "RTMatte.h"

namespace Engine {

	RTMatte::RTMatte()
		:RTMaterial(),
		m_AmbientBRDF(new RTLambertian),
		m_DiffuseBRDF(new RTLambertian)
	{
	}

	RTMatte::~RTMatte()
	{
	}

	void RTMatte::SetKa(const float ka)
	{
		m_AmbientBRDF->SetKa(ka);
	}

	void RTMatte::SetKd(const float kd)
	{
		m_DiffuseBRDF->SetKd(kd);
	}

	void RTMatte::SetCd(Texture* c)
	{
		m_AmbientBRDF->SetCd(c);
		m_DiffuseBRDF->SetCd(c);
	}

	glm::vec3 RTMatte::Shade(ShadeRec& sr)
	{
		glm::vec3 wo = -sr.ray.d;
		glm::vec3 L = m_AmbientBRDF->Rho(sr, wo) * sr.w.ambient_ptr->L(sr);
		int numLights = sr.w.lights.size();

		for (int j = 0; j < numLights; j++)
		{
			RTLight* lightPtr = sr.w.lights[j];
			glm::vec3 wi = lightPtr->GetDirection(sr);
			wi = glm::normalize(wi);
			float ndotwi = glm::dot(sr.normal, wi);
			float ndotwo = glm::dot(sr.normal, wo);

			if (ndotwi > 0.0 && ndotwo > 0.0)
			{
				bool in_shadow = false;

				if (lightPtr->CastsShadows())
				{
					Ray shadowRay(sr.local_hit_point, wi);
					in_shadow = lightPtr->InShadow(shadowRay, sr);
				}

				if(!in_shadow)
					L += m_DiffuseBRDF->f(sr, wo, wi) * lightPtr->L(sr) * ndotwi;
			}
				
		}

		return L;
	}

	glm::vec3 RTMatte::ShadeAreaLight(ShadeRec& sr)
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

				if (!in_shadow)
					L += m_DiffuseBRDF->f(sr, wo, wi) * sr.w.lights[j]->L(sr) * sr.w.lights[j]->G(sr)* ndotwi / sr.w.lights[j]->Pdf(sr);
			}

		}

		return L;
	}
}


