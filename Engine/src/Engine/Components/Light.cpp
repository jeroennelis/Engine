#include "enpch.h"

#include "Light.h"

namespace Engine {

	const unsigned int Light::ComponentType = COMP_LIGHT;

	Light::Light(Transform* transform)
		:Component("light", ComponentType), m_Transform(transform)
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
	}
	const unsigned int Light::Type() const
	{
		return 0;
	}
}