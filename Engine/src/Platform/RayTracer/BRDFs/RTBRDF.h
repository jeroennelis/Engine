#pragma once

#include "../Samplers/Sampler.h"
#include "../World/World.h"
#include "Engine/BRDF/BRDF.h"

namespace Engine {

	class RTBRDF : virtual BRDF
	{
	public:
		RTBRDF();
		~RTBRDF();

		virtual RTBRDF* clone(void)const = 0;

		inline void SetSampler(Sampler* sampler) { m_Sampler = sampler; }

		virtual glm::vec3 f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const = 0;

		virtual glm::vec3 SampleF(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi) const = 0;

		virtual glm::vec3 Rho(const ShadeRec& sr, const glm::vec3& wo) const = 0;
		
	protected:
		Sampler* m_Sampler;
	};
}