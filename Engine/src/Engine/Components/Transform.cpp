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
		:Component( "Transform" , ComponentType), m_ParentTransform(parentTransform)
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::Update()
	{
		glm::mat4 posMatrix = glm::translate(glm::mat4(1.0f), Position);

		glm::mat4 rotXMatrix = glm::rotate(glm::radians(Rotation.x), glm::vec3(1, 0, 0));
		glm::mat4 rotYMatrix = glm::rotate(glm::radians(Rotation.y), glm::vec3(0, 1, 0));
		glm::mat4 rotZMatrix = glm::rotate(glm::radians(Rotation.z), glm::vec3(0, 0, 1));
		glm::mat4 rotMatrix = rotXMatrix * rotYMatrix * rotZMatrix;

		glm::mat4 scaleMatrix = glm::scale(glm::vec3(Scale.x, Scale.y, Scale.z));
		glm::mat4 test = posMatrix * rotMatrix * scaleMatrix;

		TransformationMatrix = posMatrix * rotMatrix * scaleMatrix;
		if (m_ParentTransform)
		{
			TransformationMatrix = m_ParentTransform->TransformationMatrix  * TransformationMatrix ;
		}
	}

	void Transform::RenderInspectorInfo()
	{
		bool open = ImGui::TreeNode(m_Name.c_str());
		bool dropsource = ImGui::BeginDragDropSource();
		if (dropsource)
		{
			std::string testpayload = "testpayload";
			ImGui::EndDragDropSource();
		}
		bool droptarget = ImGui::BeginDragDropTarget();
		if (droptarget)
		{
			
			if (const ImGuiPayload* pl = ImGui::AcceptDragDropPayload("transform"))
			{
				EN_CORE_TRACE("droppped");
			}
			ImGui::EndDragDropTarget();
		}
		
		if (open)
		{
			ImGui::DragFloat3( "Translate" ,	(float*)&Position,	0.1f, -1000, 1000);
			ImGui::DragFloat3( "Rotate" ,		(float*)&Rotation,	0.1f, -1000, 1000);
			ImGui::DragFloat3( "Scale" ,		(float*)&Scale,		0.1f, -1000, 1000);
			ImGui::TreePop();
		}
		
		ImGui::Separator();
	}
	void Transform::CalculateTransform()
	{
	}
}


