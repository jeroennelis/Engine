#pragma once

#include  "Engine/Layer.h" 

#include  "Engine/Events/KeyEvent.h" 
#include  "Engine/Events/Event.h" 
#include  "Engine/Events/MouseEvent.h" 

#include  "Engine/Events/ApplicationEvent.h" 
#include  "Engine/Components/TestComponent.h" 

#include  "Engine/XMLParser/XMLWriter.h" 



namespace Engine {

	class ENGINE_API ImGuiLayer : public Layer
	{

	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;

		void Begin();
		void End();

		void RenderMenuBar();
		void RenderInspectorWindow();
		void RenderGameWindow();
		void RenderSceneWindow();
		void RenderHierarchyWindow();
		void RenderConsoleWindow();
		void RenderProjectWindow();

		void RT(int nrOfSamples);

	private:
		void ToggleStatistics();
		void AddEmptyGameObject();
		glm::vec3 PickMouse(int windowPosX, int windowPosY, int imGuiWindowWidth, int imGuiWindowHeigth, int mouseX, int mouseY);
		void AddCube();
		void AddSphere();


		std::thread test;


	private:
		float m_time = 0;

		static bool m_ShowStatistics;
	};
}
