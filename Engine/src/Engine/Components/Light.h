#pragma once
#include "Component.h"
#include "Transform.h"

namespace Engine {

	class Light : public Component
	{

	public:
		Light(Transform* transfomr );
		~Light();

	private:
		const static unsigned int ComponentType;

		Transform* m_Transform;
		glm::vec4 m_Color;

		// Inherited via Component
		virtual void Update() override;
		virtual void RenderInspectorInfo() override;
		virtual const unsigned int Type() const override;
	};
}