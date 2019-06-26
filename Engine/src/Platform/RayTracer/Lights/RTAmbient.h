#pragma once

#include "RTLight.h"

namespace Engine {

	class RTAmbient : public RTLight
	{
	public:
		RTAmbient();
		~RTAmbient();

		virtual glm::vec3 GetDirection(ShadeRec& sr) override;

		virtual glm::vec3 L(ShadeRec& sr) override;

		inline void SetLs(const float ls) { m_Ls = ls; }
		inline void SetColor(const glm::vec3& color) { m_Color = color; }

	private:
		float m_Ls;		//emmissive material
		glm::vec3 m_Color;


		

	};
}
