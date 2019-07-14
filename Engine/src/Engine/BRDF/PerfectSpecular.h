#pragma once

#include "BRDF.h"
#include "Engine/Textures/Texture.h"

namespace Engine {

	class PerfectSpecular : public BRDF
	{
	public:
		PerfectSpecular();

		inline void SetKr(const float kr) { m_Kr = kr; }
		inline void SetCr(Texture* cr) { m_Cr = cr; }

	protected:
		float m_Kr;
		Texture* m_Cr;
	};
}
