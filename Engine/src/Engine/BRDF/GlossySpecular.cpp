#include "enpch.h"
#include "GlossySpecular.h"

Engine::GlossySpecular::GlossySpecular()
	:BRDF(),
	m_Ks(0.0),
	m_Cs(),
	m_Exp(1.0)
{
}
