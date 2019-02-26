#include  "enpch.h"
#include  "Transform.h" 
#include  "imgui.h" 

namespace Engine {

	const unsigned int Transform::ComponentType = COMP_TRANSFORM;

	Transform::Transform()
		:Component( "Transform" , ComponentType)
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
			ImGui::DragFloat3( "Translate" , (float*)&Position, 1, -1000, 1000);
			ImGui::DragFloat3( "Rotate" ,	(float*)&Rotation, 1, -1000, 1000);
			ImGui::DragFloat3( "Scale" ,		(float*)&Scale, 1, -1000, 1000);
			ImGui::TreePop();
		}
		ImGui::Separator();
	}
}


