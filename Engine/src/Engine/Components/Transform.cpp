#include  "enpch.h"
#include  "Transform.h" 
#include  "imgui.h" 
#include <glm/gtx/transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtx\quaternion.hpp>

namespace Engine {

	const unsigned int Transform::ComponentType = COMP_TRANSFORM;

	Transform::Transform(Transform* parentTransform)
		:Component("Transform", ComponentType), m_ParentTransform(parentTransform)
	{
		CalculateMatrix();
	}

	Transform::~Transform()
	{
	}

	void Transform::Update()
	{
		CalculateMatrix();
	}

	void Transform::RenderInspectorInfo()
	{
		static bool open = true;
		ImGui::SetNextTreeNodeOpen(open);
		if (ImGui::TreeNode(m_Name.c_str()))
		{
			ImGui::DragFloat3("Translate", (float*)& Position, 0.1f, -1000, 1000);
			ImGui::DragFloat3("Rotate", (float*)& Rotation, 0.1f, -1000, 1000);
			ImGui::DragFloat3("Scale", (float*)& Scale, 0.1f, -1000, 1000);
			ImGui::TreePop();
			open = true;
		}
		else
		{
			open = false;
		}

		ImGui::Separator();

		CalculateMatrix();
	}
	void Transform::CalculateMatrix()
	{
		glm::mat4 posMatrix = glm::translate(glm::mat4(1.0f), Position);

		glm::mat4 rotXMatrix = glm::rotate(glm::radians(Rotation.x), glm::vec3(1, 0, 0));
		glm::mat4 rotYMatrix = glm::rotate(glm::radians(Rotation.y), glm::vec3(0, 1, 0));
		glm::mat4 rotZMatrix = glm::rotate(glm::radians(Rotation.z), glm::vec3(0, 0, 1));
		glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

		glm::mat4 scaleMatrix = glm::scale(glm::vec3(Scale.x, Scale.y, Scale.z));
		glm::mat4 test = posMatrix * rotMatrix * scaleMatrix;

		TransformationMatrix = posMatrix * rotMatrix * scaleMatrix;
		if (m_ParentTransform)
		{
			TransformationMatrix = m_ParentTransform->TransformationMatrix * TransformationMatrix;
		}
	}

	void Transform::CalculateComponents()
	{
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::quat rot;
		glm::decompose(TransformationMatrix, Scale, rot, Position, skew, perspective);
		Rotation = glm::degrees(glm::eulerAngles( rot));


		/*Rotation[0] = glm::degrees(atan2f(TransformationMatrix[1][2], TransformationMatrix[2][2]));
		Rotation[1] = glm::degrees(atan2f(-TransformationMatrix[0][2], sqrtf(TransformationMatrix[1][2] * TransformationMatrix[1][2] + TransformationMatrix[2][2] * TransformationMatrix[2][2])));
		Rotation[2] = glm::degrees(atan2f(TransformationMatrix[0][1], TransformationMatrix[0][0]));*/

		//std::cout << "x: " << Rotation.x << ",\t y: " << Rotation.y << ",\t z: " << Rotation.z << std::endl;
	}

}

