#pragma once
#include "Component.h"
#include "Transform.h"
#include "Engine/Events/Event.h"


namespace Engine {

	class Camera : public Component
	{
	public:
		Camera(Transform* transform);
		~Camera();

		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; };
		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; };
		inline const Transform* GetTransform() const { return m_Transform; };

		void OnEvent(Event & event);

	private:
		const static unsigned int ComponentType;

		Transform* m_Transform;

		// Inherited via Component
		virtual void Update() override;
		virtual void RenderInspectorInfo() override;
		virtual const unsigned int Type() const override;

		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;

	private:
		void CalculateViewMatrix();
		void CalculateProjectionMatrix();

		//hack
		std::pair<float, float> oldMousePosition;
	};
}