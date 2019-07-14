#pragma once

#include "BRDF.h"
#include "Engine/Textures/Texture.h"

namespace Engine
{

	class Lambertian : public BRDF
	{

	public:
		Lambertian();

		inline void SetKd(const float kd) { m_Kd = kd; }
		inline void SetCd(Texture* cd) { m_Cd = cd; }

		inline void SetKa(const float ka) { m_Kd = ka; }


	protected:
		float m_Kd;
		Texture* m_Cd;
	};
}
