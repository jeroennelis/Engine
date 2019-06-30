#pragma once

#include "../Utilities/Ray.h"



namespace Engine {

	class ShadeRec;

	class RTLight
	{
	public:
		RTLight();
		~RTLight();

		virtual glm::vec3 GetDirection(ShadeRec& sr) = 0;

		virtual glm::vec3 L(ShadeRec& sr) = 0;

		virtual bool InShadow(const Ray& ray, const ShadeRec& sr) const;

		inline bool CastsShadows() { return m_Shadows; }
		inline void EnableShadows(bool enabled) { m_Shadows = enabled; }

	protected:
		float m_Ls;
		glm::vec3 m_Color;

	private:
		bool m_Shadows;

	};
}