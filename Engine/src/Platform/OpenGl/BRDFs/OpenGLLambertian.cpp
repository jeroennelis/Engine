#include "enpch.h"
#include "OpenGLLambertian.h"

namespace Engine {
	void OpenGLLambertian::Bind()
	{

	}

	void OpenGLLambertian::RenderInspectorInfo()
	{
		
		ImGui::DragFloat("Kd", &m_Kd, 0.01f, 0.0f, 1.0f);
		m_Cd->RenderInspectorInfo();
		
	}
}


