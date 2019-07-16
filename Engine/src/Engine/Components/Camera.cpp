#include "enpch.h"

#include "Camera.h"
#include <glm/gtx/transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtx\quaternion.hpp>
#include "Engine/Application.h"
#include "Engine/Input.h"
#include "Engine/MouseButtonCodes.h"
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Engine {

	const unsigned int Camera::ComponentType = COMP_CAMERA;


	Camera::Camera(Transform* transform)
		:Component("Camera", ComponentType), m_Transform(transform), m_ViewMatrix(glm::mat4(1.0))
	{
	}
	Camera::~Camera()
	{
	}

	void Camera::OnEvent(Event & event)
	{
	}
	
	void Camera::Update()
	{
		CalculateViewMatrix();
		CalculateProjectionMatrix();

		std::pair<float, float> newMousePosition = Input::GetMousePosition();
		if (Input::IsMouseButtonPressed(EN_MOUSE_BUTTON_2))
		{
			float dx = oldMousePosition.first - newMousePosition.first;
			float dy = oldMousePosition.second - newMousePosition.second;
			m_Transform->Rotation.x += dy/*temp*//10;/*temp*/
			m_Transform->Rotation.y += dx/*temp*//10;/*temp*/
		}

		if (Input::IsMouseButtonPressed(EN_MOUSE_BUTTON_3))
		{
			float dx = oldMousePosition.first - newMousePosition.first;
			float dy = oldMousePosition.second - newMousePosition.second;
			m_Transform->Position.x -= dx/*temp*/ /100/*temp*/;
			m_Transform->Position.y += dy/*temp*/ /100/*temp*/;
		}

		oldMousePosition = newMousePosition;

	}
	void Camera::RenderInspectorInfo()
	{
	}

	const unsigned int Camera::Type() const
	{
		return 0;
	}

	void Camera::CalculateViewMatrix()
	{
		glm::mat4 posMatrix = glm::translate(glm::mat4(1.0f), m_Transform->Position);

		glm::mat4 rotXMatrix = glm::rotate(glm::radians(m_Transform->Rotation.x), glm::vec3(1, 0, 0));
		glm::mat4 rotYMatrix = glm::rotate(glm::radians(m_Transform->Rotation.y), glm::vec3(0, 1, 0));
		glm::mat4 rotZMatrix = glm::rotate(glm::radians(m_Transform->Rotation.z), glm::vec3(0, 0, 1));
		glm::mat4 rotMatrix = rotXMatrix * rotYMatrix * rotZMatrix;

		glm::mat4 scaleMatrix = glm::scale(glm::vec3(m_Transform->Scale.x, m_Transform->Scale.y, m_Transform->Scale.z));

		/*if (Application::Get().GetOpenVRContext())
		{
			m_ViewMatrix = glm::inverse(Application::Get().GetOpenVRContext()->GetDevicePoses()[vr::k_unTrackedDeviceIndex_Hmd]);
			glm::quat rot;
			glm::vec3 skew;
			glm::vec4 pers;
			glm::decompose(m_ViewMatrix, m_Transform->Scale, rot, m_Transform->Position, skew, pers);
			m_Transform->Rotation = glm::eulerAngles(rot);
		}
		else*/
			m_ViewMatrix = (rotMatrix * posMatrix * scaleMatrix);
	}

	void Camera::CalculateProjectionMatrix()
	{
		float aspectRatio = (float)Application::Get().GetWindow().GetWidth() / (float)Application::Get().GetWindow().GetHeight();
		//fov
		float y_scale = (float)((1.0f / glm::tan(glm::radians(90 / 2.0f))) * aspectRatio);
		float x_scale = y_scale / aspectRatio;
		float frustum_length = 1000 - 0.1f;

		m_ProjectionMatrix = glm::mat4();
		m_ProjectionMatrix[0][0] = x_scale;
		m_ProjectionMatrix[1][1] = y_scale;
		m_ProjectionMatrix[2][2] = -((1000 + 0.1f) / frustum_length);
		m_ProjectionMatrix[2][3] = -1;
		m_ProjectionMatrix[3][2] = -((2 * 0.1f * 1000) / frustum_length);
		m_ProjectionMatrix[3][3] = 0;

		
	}
}