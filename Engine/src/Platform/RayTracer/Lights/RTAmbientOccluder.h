#pragma once

#include "RTLight.h"
#include "../Samplers/Sampler.h"

namespace Engine {

	class RTAmbientOccluder : public RTLight
	{
	public:
		RTAmbientOccluder();
		~RTAmbientOccluder();

		void SetSampler(Sampler* sampler);

		virtual glm::vec3 GetDirection(ShadeRec& sr);

		virtual bool InShadow(const Ray& ray, const ShadeRec& sr) const;

		virtual glm::vec3 L(ShadeRec& sr);

	private:
		glm::vec3 m_U, m_V, m_W;
		Sampler* m_Sampler;
		glm::vec3 m_MinAmount;
	};
	
}