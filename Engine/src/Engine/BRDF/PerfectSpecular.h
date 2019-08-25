#pragma once

#include "BRDF.h"
#include "Engine/Textures/Texture_temp.h"

namespace Engine {

	class PerfectSpecular : public BRDF
	{
	public:
		PerfectSpecular();

		inline void SetKr(const float kr) { m_Kr = kr; }
		inline void SetCr(Texture_temp* cr) { m_Cr = cr; }

		inline float GetKr() { return m_Kr;}
		inline Texture_temp* GetCr() { return m_Cr; }

	protected:
		float m_Kr;
		Texture_temp* m_Cr;
	};
}
