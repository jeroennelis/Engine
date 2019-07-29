#pragma once
#include "Component.h"
#include "Transform.h"
#include "Engine/Events/Event.h"


namespace Engine {

	struct CameraProperties
	{
		float NearPlane, FarPlane;
		float FOV;

		CameraProperties(float nearPlane = 0.1f,
			float farPlane = 1000.0f,
			float fov = 90.0f)
			:NearPlane(nearPlane), FarPlane(farPlane), FOV(fov)
		{}
	};

	class Camera : public Component
	{
	public:
		Camera(Transform* transform, const CameraProperties& props);
		~Camera();

		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; };
		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; };
		inline Transform* GetTransform() const { return m_Transform; };

		inline const float GetNearPlane() { return m_Properties.NearPlane; }
		inline const float GetFarPlane() { return m_Properties.FarPlane; }
		inline const float GetFOV() { return m_Properties.FOV; }

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

		CameraProperties m_Properties;

	private:
		void CalculateViewMatrix();
		void CalculateProjectionMatrix();

		//hack
		std::pair<float, float> oldMousePosition;
	};
}