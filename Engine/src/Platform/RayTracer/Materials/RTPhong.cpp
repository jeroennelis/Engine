#include "enpch.h"
#include "RTPhong.h"
#include "../World/World.h"
#include "../Utilities/ShadeRec.h"


namespace Engine {

	RTPhong::RTPhong()
		:m_AmbientBRDF(new Lambertian),
		m_DiffuseBRDF(new Lambertian),
		m_SpecularBRDF(new GlossySpecular)
	{
	}
	RTPhong::~RTPhong()
	{
	}

	glm::vec3 RTPhong::Shade(ShadeRec & sr)
	{
		glm::vec3 wo = -sr.ray.d;
		glm::vec3 L = m_AmbientBRDF->Rho(sr, wo) * sr.w.ambient_ptr->L(sr);
		int num_lights = sr.w.lights.size();

		for (int j = 0; j < num_lights; j++)
		{
			glm::vec3 wi = sr.w.lights[j]->GetDirection(sr);
			float nDotWi = glm::dot(sr.normal, wi);

			if (nDotWi > 0.0)
			{
				bool inShadow = false;

				if (sr.w.lights[j]->CastsShadows())
				{
					Ray shadowRay(sr.hit_point, wi);
					inShadow = sr.w.lights[j]->InShadow(shadowRay, sr);
				}
				if (!inShadow)
					L += (m_DiffuseBRDF->f(sr, wo, wi) + m_SpecularBRDF->f(sr, wo, wi)) * sr.w.lights[j]->L(sr) * nDotWi;
			}

		}
		return L;
	}
	void RTPhong::SetKa(const float ka)
	{
		m_AmbientBRDF->SetReflectionCoefficient(ka);
	}
	void RTPhong::SetKd(const float kd)
	{
		m_DiffuseBRDF->SetReflectionCoefficient(kd);
	}
	void RTPhong::SetKs(const float ks)
	{
		m_SpecularBRDF->SetKs(ks);
	}

	void RTPhong::SetExp(const float exp)
	{
		m_SpecularBRDF->SetExp(exp);
	}

	void RTPhong::SetCd(const glm::vec3 & c)
	{
		m_AmbientBRDF->SetColor(c);
		m_DiffuseBRDF->SetColor(c);
		m_SpecularBRDF->SetCs(c);
	}
}


