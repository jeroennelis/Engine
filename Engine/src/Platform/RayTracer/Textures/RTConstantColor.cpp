#include "enpch.h"
#include "RTConstantColor.h"

namespace Engine {

	glm::vec3 RTConstantColor::GetColor(const ShadeRec& sr) const
	{
		return m_Color;
	}
}