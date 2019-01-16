#include "enpch.h"
#include "TestComponent.h"
#include "imgui.h"

namespace Engine {
	
	const unsigned int TestComponent::ComponentType = COMP_TEST;
	
	TestComponent::TestComponent()
		:Component("TestComponent", ComponentType)
	{
	}

	void Engine::TestComponent::Update()
	{
	}

	void TestComponent::RenderInspectorInfo()
	{
		if (ImGui::TreeNode(m_Name.c_str()))
		{
			/*ImGui::InputFloat("Pitch", &Pitch, 1);
			ImGui::InputFloat("Yaw", &Yaw, 1);
			ImGui::InputFloat("Roll", &Roll, 1);
			ImGui::InputFloat("FOV", &FOV, 1);
			ImGui::InputFloat("NEAR", &NEAR_PLANE, 1);
			ImGui::InputFloat("FAR", &FAR_PLANE, 1);
			ImGui::Checkbox("player", &focussedAroundPlayer);*/

			ImGui::TreePop();
		}
	}
}



