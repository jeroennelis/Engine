#pragma once
#include  "Component.h" 
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Engine {

	class Transform : public Component
	{
	public:
		Transform(Transform* ParentTransform = nullptr);
		~Transform();

		virtual void Update() override;

		virtual void RenderInspectorInfo() override;

		inline virtual const unsigned int Type() const override { return ComponentType; }

		const static unsigned int ComponentType;

		glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 Scale = glm::vec3(1.0f,1.0f,1.0f);

		glm::mat4 TransformationMatrix;

	private:
		void CalculateTransform();

	private:
		Transform* m_ParentTransform;
	};
}



