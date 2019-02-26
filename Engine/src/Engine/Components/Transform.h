#pragma once
#include  "Component.h" 
#include <Maths/src/Vector3.h>

namespace Engine {

	class Transform : public Component
	{
	public:
		Transform();
		~Transform();

		virtual void Update() override;

		virtual void RenderInspectorInfo() override;

		inline virtual const unsigned int Type() const override { return ComponentType; }

		const static unsigned int ComponentType;

		Maths::Vector3 Position;
		Maths::Vector3 Rotation;
		Maths::Vector3 Scale = Maths::Vector3(1.0f,1.0f,1.0f);
	};
}



