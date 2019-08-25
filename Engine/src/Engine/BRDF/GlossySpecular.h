#pragma once

#include "BRDF.h"
#include "Engine/Textures/Texture_temp.h"

namespace Engine{

	class GlossySpecular : public BRDF
	{
	public:
		GlossySpecular();

		inline void SetKs(const float ks) { m_Ks = ks; }
		inline void SetCs(Texture_temp* cs) { m_Cs = cs; }
		inline void SetExp(const float exp) { m_Exp = exp; }

		inline float GetKs() { return m_Ks; }
		inline Texture_temp* GetCs() { return m_Cs; }
		inline float GetExp() { return m_Exp; }

	protected:
		float m_Ks;
		Texture_temp* m_Cs;
		float m_Exp;
	};
}
