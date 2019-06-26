#include "enpch.h"
#include "RTAmbient.h"

namespace Engine {
	RTAmbient::RTAmbient()
		:m_Ls(1.0), m_Color(1.0)//white
	{
	}
	RTAmbient::~RTAmbient()
	{
	}
	glm::vec3 RTAmbient::GetDirection(ShadeRec& sr)
	{
		return glm::vec3(0.0);
	}

	glm::vec3 RTAmbient::L(ShadeRec& sr)
	{
		return (m_Ls * m_Color);
	}
}


