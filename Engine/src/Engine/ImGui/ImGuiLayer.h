#pragma once

#include "Engine/Layer.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/Event.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Components/TestComponent.h"

#include "Engine/XMLParser/XMLWriter.h"



namespace Engine {

	class ENGINE_API ImGuiLayer : public Layer
	{

	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);

		void RenderMenuBar();
		void RenderInspectorWindow();
		void RenderGameWindow();
		void RenderHierarchyWindow();
		void RenderConsoleWindow();


	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnwindowResizeEvent(WindowResizeEvent& e);

		void ToggleStatistics();
		void AddEmptyGameObject();


	private:
		float m_time = 0;

		static bool m_ShowStatistics;
	};
}
