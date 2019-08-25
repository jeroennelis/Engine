#pragma once
#include "Component.h"
#include "Transform.h"

namespace Engine {

	class Light : public Component
	{

	public:
		Light(Transform* transform );
		virtual ~Light();

		inline Transform* GetTransform() { return m_Transform; }
		inline glm::vec4* GetColor() { return &m_Color; }
		inline glm::vec3 GetAttenuation() { return m_Attenuation; }


	private:
		const static unsigned int ComponentType;

		Transform* m_Transform;
		glm::vec4 m_Color;
		glm::vec3 m_Attenuation;

		// Inherited via Component
		virtual void Update() override;
		virtual void RenderInspectorInfo() override;
		virtual const unsigned int Type() const override;
	};
}