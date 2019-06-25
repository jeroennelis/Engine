#pragma once

#include "../Samplers/Sampler.h"
#include "../World/World.h"

namespace Engine {

	class BRDF
	{
		BRDF();
		~BRDF();

		inline void SetSampler(Sampler* sampler) { m_Sampler = sampler; }

		virtual glm::vec3 f(const ShadeRec& sr, const glm::vec3& wi, const glm::vec3& wo) const = 0;

		virtual glm::vec3 SampleF(const ShadeRec& sr, glm::vec3& wi, const glm::vec3& wo) const = 0;

		virtual glm::vec3 Rho(const ShadeRec& sr, const glm::vec3& wo) const = 0;
		
	protected:
		Sampler* m_Sampler;
	};
}