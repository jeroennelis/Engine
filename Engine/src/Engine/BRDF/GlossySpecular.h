#pragma once

#include "BRDF.h"
#include "Engine/Textures/Texture.h"

namespace Engine{

	class GlossySpecular : public BRDF
	{
	public:
		GlossySpecular();

		inline void SetKs(const float ks) { m_Ks = ks; }
		inline void SetCs(Texture* cs) { m_Cs = cs; }
		inline void SetExp(const float exp) { m_Exp = exp; }

	protected:
		float m_Ks;
		Texture* m_Cs;
		float m_Exp;
	};
}
