#include "enpch.h"

#include "Light.h"
#include "imgui.h"

namespace Engine {

	const unsigned int Light::ComponentType = COMP_LIGHT;

	Light::Light(Transform* transform)
		:Component("light", ComponentType), m_Transform(transform), m_Color(1.0,1.0,1.0,1.0), m_Attenuation(1.0,0.0,0.0)
	{
	}

	Light::~Light()
	{
	}

	
	void Light::Update()
	{
	}
	void Light::RenderInspectorInfo()
	{
		ImGui::ColorEdit4("color", &m_Color[0]);
		ImGui::DragFloat3("attenuation", &m_Attenuation[0]);
	}

	const unsigned int Light::Type() const
	{
		return ComponentType;
	}
}