#include "enpch.h"

#include "OrthographicCamera.h"

namespace Engine {

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float n, float f)
		:m_ProjectionMatrix(glm::ortho(left, right, bottom, top, n, f)), m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * 
			glm::rotate(glm::mat4(1.0f), m_Rotation, glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}