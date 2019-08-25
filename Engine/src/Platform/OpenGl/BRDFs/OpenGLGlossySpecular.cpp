#include "enpch.h"
#include "OpenGLGlossySpecular.h"

#include "imgui.h"

namespace Engine {
	void OpenGLGlossySpecular::RenderInspectorInfo()
	{
		m_Cs->RenderInspectorInfo();
		ImGui::DragFloat("Ks", &m_Ks, 0.1f, 0.0f, 1.0f);
		ImGui::DragFloat("Epsilon", &m_Exp, 0.1f, 0.0f, 1000.0f); 
	}
}