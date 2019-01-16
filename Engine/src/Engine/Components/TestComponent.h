#pragma once
#include "Engine/Components/Component.h"

namespace Engine {

	class ENGINE_API TestComponent : public Component
	{
	public:

		TestComponent();
		virtual ~TestComponent() {};

		virtual void Update() override;
		

		const static unsigned int ComponentType;

		virtual void RenderInspectorInfo() override;
	};
}

