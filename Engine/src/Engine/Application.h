#pragma once

#include "Core.h"

#include "window.h"
#include "Engine/LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Engine/XMLParser/XMLReader.h"

#include "Engine/ImGui/ImGuiLayer.h"


namespace Engine {

	class FrameBuffer;

	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event &e);

		void PushLayer(Layer* layer);
		void PushOverLay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
		inline FrameBuffer* GetGameFrameBuffer() { return m_GameFrameBuffer; }

	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		FrameBuffer* m_GameFrameBuffer;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}



