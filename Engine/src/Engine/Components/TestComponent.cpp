#include  "enpch.h" 
#include  "TestComponent.h" 
#include  "imgui.h" 

namespace Engine {
	
	const unsigned int TestComponent::ComponentType = COMP_TEST;
	
	TestComponent::TestComponent()
		:Component( "TestComponent" , ComponentType)
	{
	}

	void Engine::TestComponent::Update()
	{
	}

	void TestComponent::RenderInspectorInfo()
	{
		if (ImGui::TreeNode(m_Name.c_str()))
		{
			ImGui::LabelText("", "this is a test component");

			ImGui::TreePop();
		}
		ImGui::Separator();
	}
}



