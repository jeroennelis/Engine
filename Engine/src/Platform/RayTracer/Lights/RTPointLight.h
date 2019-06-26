#pragma once

#include "RTLight.h"

namespace Engine {

	class RTPointLight : public RTLight
	{
	public:
		RTPointLight();
		~RTPointLight();

		virtual glm::vec3 GetDirection(ShadeRec& sr) override;

		virtual glm::vec3 L(ShadeRec& sr) override;

		inline void SetLs(const float ls) { m_Ls = ls; }
		inline void SetColor(const glm::vec3& color) { m_Color = color; }
		inline void SetLocation(const glm::vec3& location) { m_Location = location; }

	private:
		float m_Ls;
		glm::vec3 m_Color;
		glm::vec3 m_Location;
	};
}
