#include "enpch.h"
#include "RenderCompont.h"


namespace Engine {

	const unsigned int RenderComponent::ComponentType = COMP_RENDERER;

	RenderComponent::RenderComponent(const std::string& name)
		:Component(name, ComponentType)
	{
	}

	const unsigned int Engine::RenderComponent::Type() const
	{
		return ComponentType;
	}

}