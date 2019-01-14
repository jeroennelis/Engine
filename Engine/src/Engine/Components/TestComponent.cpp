#include "enpch.h"
#include "TestComponent.h"

namespace Engine {
	
	const unsigned int TestComponent::ComponentType = COMP_TEST;
	
	TestComponent::TestComponent()
		:Component("TestComponent", ComponentType)
	{
	}

	void Engine::TestComponent::Update()
	{
		EN_CORE_INFO("update testcomponent");
	}
}



