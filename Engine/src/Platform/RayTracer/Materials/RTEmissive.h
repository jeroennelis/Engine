#pragma once

#include "RTMaterial.h"

#include "../Utilities/ShadeRec.h"

namespace Engine {

	class RTEmissive : public RTMaterial
	{
	public:
		RTEmissive();
		~RTEmissive();

		inline void ScaleRadance(const float ls) { m_Ls = ls; }

		inline void SetCe(const glm::vec3& ce) { m_Ce = ce; }

		glm::vec3 GetLe(ShadeRec& sr) const override;

		virtual glm::vec3 Shade(ShadeRec& sr) override;

		virtual glm::vec3 ShadeAreaLight(ShadeRec& sr) override;

	private:
		float m_Ls;
		glm::vec3 m_Ce;
	};
}