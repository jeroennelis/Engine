#include "enpch.h"
#include "RTPhong.h"
#include "../World/World.h"
#include "../Utilities/ShadeRec.h"


namespace Engine {

	RTPhong::RTPhong()
		:Phong(new RTLambertian, new RTLambertian, new RTGlossySpecular, nullptr)		
	{
	}
	RTPhong::~RTPhong()
	{
	}

	glm::vec3 RTPhong::Shade(ShadeRec & sr)
	{
		glm::vec3 wo = -sr.ray.d;
		glm::vec3 L = m_AmbientBRDF->Rho(sr, wo) * sr.w->ambient_ptr->L(sr);
		int num_lights = sr.w->lights.size();

		for (int j = 0; j < num_lights; j++)
		{
			RTLight* lightPtr = sr.w->lights[j];
			glm::vec3 wi = lightPtr->GetDirection(sr);
			wi = glm::normalize(wi);
			float nDotWi = glm::dot(sr.normal, wi);
			float nDotWo = glm::dot(sr.normal, wo);

			if (nDotWi > 0.0 && nDotWo > 0.0)
			{
				bool inShadow = false;

				if (lightPtr->CastsShadows())
				{
					Ray shadowRay(sr.hit_point, wi);
					inShadow = lightPtr->InShadow(shadowRay, sr);
				}
				if (!inShadow)
					L += (m_DiffuseBRDF->f(sr, wo, wi) + m_SpecularBRDF->f(sr, wo, wi)) * lightPtr->L(sr) * nDotWi;
			}

		}
		return L;
	}
	glm::vec3 RTPhong::ShadeAreaLight(ShadeRec& sr)
	{
		glm::vec3 wo = -sr.ray.d;
		glm::vec3 L = m_AmbientBRDF->Rho(sr, wo) * sr.w->ambient_ptr->L(sr);
		int num_lights = sr.w->lights.size();

		for (int j = 0; j < num_lights; j++)
		{
			glm::vec3 wi = sr.w->lights[j]->GetDirection(sr);
			float nDotWi = glm::dot(sr.normal, wi);

			if (nDotWi > 0.0)
			{
				bool inShadow = false;

				if (sr.w->lights[j]->CastsShadows())
				{
					Ray shadowRay(sr.local_hit_point, wi);
					inShadow = sr.w->lights[j]->InShadow(shadowRay, sr);
				}
				if (!inShadow)
					L += (m_DiffuseBRDF->f(sr, wo, wi) + m_SpecularBRDF->f(sr, wo, wi)) * sr.w->lights[j]->L(sr) * sr.w->lights[j]->G(sr) * nDotWi / sr.w->lights[j]->Pdf(sr);
			}

		}
		return L;
	}
}


