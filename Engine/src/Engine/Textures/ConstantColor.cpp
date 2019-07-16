#include "enpch.h"
#include "ConstantColor.h"
#include "imgui.h"

namespace Engine {

	void ConstantColor::RenderInspectorInfo()
	{
		ImGui::ColorEdit4("color", &m_Color[0]);
	}

	glm::vec3 ConstantColor::GetColor(const ShadeRec& sr) const
	{
		return m_Color;
	}
}