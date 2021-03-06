#pragma once

#include "Core.h"

#include "window.h"
#include "Engine/LayerStack.h" 
#include "Events/Event.h" 
#include "Events/ApplicationEvent.h" 
#include "Engine/XMLParser/XMLReader.h" 

#include "Engine/ImGui/ImGuiLayer.h" 

#include "Platform/OpenGl/Texture.h"


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
		inline LayerStack& GetLayerStack() { return m_LayerStack; }

	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}



