#include "enpch.h"

#include "Light.h"

namespace Engine {

	const unsigned int Light::ComponentType = COMP_LIGHT;

	Light::Light(Transform* transform)
		:Component("light", ComponentType), m_Transform(transform)
	{
	}

	
	void Light::Update()
	{
	}
	void Light::RenderInspectorInfo()
	{
	}
	const unsigned int Light::Type() const
	{
		return 0;
	}
}