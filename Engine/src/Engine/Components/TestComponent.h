#pragma once
#include  "Component.h" 

namespace Engine {

	class ENGINE_API TestComponent : public Component
	{
	public:

		TestComponent();
		virtual ~TestComponent() {};

		virtual void Update() override;
		
		virtual void RenderInspectorInfo() override;
		inline virtual const unsigned int Type() const override { return ComponentType; }

		const static unsigned int ComponentType;
	};
}

