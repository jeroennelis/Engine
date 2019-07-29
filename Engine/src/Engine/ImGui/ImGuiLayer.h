#pragma once

#include  "Engine/Layer.h" 

#include  "Engine/Events/KeyEvent.h" 
#include  "Engine/Events/Event.h" 
#include  "Engine/Events/MouseEvent.h" 

#include  "Engine/Events/ApplicationEvent.h" 
#include  "Engine/Components/TestComponent.h" 

#include  "Engine/XMLParser/XMLWriter.h" 
#include <imgui.h>
#include "..//imguizmo/ImGuizmo.h"



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
		void RenderToolBar();

		void RT(int nrOfSamples);

	private:
		void ToggleStatistics();
		void AddEmptyGameObject();
		glm::vec3 PickMouse(int windowPosX, int windowPosY, int imGuiWindowWidth, int imGuiWindowHeigth, int mouseX, int mouseY);
		void AddCube();
		void AddSphere();

		void EditTransform(const float* cameraView, float* cameraProjection, float* matrix, ImVec2 origin, ImVec2 size);


		std::thread test;


	private:
		float m_time = 0;

		static bool m_ShowStatistics;



		ImGuizmo::OPERATION mCurrentGizmoOperation = ImGuizmo::TRANSLATE;

		float cameraProjection[16];
		float objectMatrix[16] =
		{ 1.f, 0.f, 0.f, 0.f,
		  0.f, 1.f, 0.f, 0.f,
		  0.f, 0.f, 1.f, 0.f,
		  0.f, 0.f, 0.f, 1.f };

		const float identityMatrix[16] =
		{ 1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f };

		float cameraView[16] =
		{ 1.f, 0.f, 0.f, 0.f,
		  0.f, 1.f, 0.f, 0.f,
		  0.f, 0.f, 1.f, 0.f,
		  0.f, 0.f, 0.f, 1.f };

		bool isPerspective = false;
		float fov = 27.f;
		float viewWidth = 10.f; // for orthographic
		float camYAngle = 165.f / 180.f * 3.14159f;
		float camXAngle = 52.f / 180.f * 3.14159f;
		float camDistance = 8.f;
		
	};
}
