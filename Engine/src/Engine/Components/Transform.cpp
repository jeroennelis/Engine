#include "enpch.h"
#include "Transform.h"
#include "imgui.h"

namespace Engine {

	const unsigned int Transform::ComponentType = COMP_TRANSFORM;

	Transform::Transform()
		:Component("Transform", ComponentType)
	{
	}


	Transform::~Transform()
	{
	}

	void Transform::Update()
	{
		
	}

	void Transform::RenderInspectorInfo()
	{
		if (ImGui::TreeNode(m_Name.c_str()))
		{
			ImGui::InputFloat3("Translate", (float*)&Position, 3);
			ImGui::InputFloat3("Rotate",	(float*)&Rotation, 3);
			ImGui::InputFloat3("Scale",		(float*)&Scale, 3);
			ImGui::TreePop();
		}
	}
}


