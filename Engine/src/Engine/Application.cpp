#include  "enpch.h" 
#include  "Application.h" 

#include "Input.h" 

#include "Logic/LogicLayer.h"
#include "Renderer/Renderer.h"
#include "Renderer/Buffer.h"
#include "image.h"

namespace Engine {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr; 


	Application::Application()
	{
		EN_CORE_ASSERT(!s_Instance, Application already exists!);
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create(Renderer::GetAPI()));
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_Window->SetVSync(true );
		
		Renderer::Create();

		RTTexture = new OpenGLTexture();
				
		PushLayer(new LogicLayer());
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event & e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			//EN_CORE_TRACE(e.ToString());
			(*--it)->OnEvent(e);
			if (e.Handled())
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
			Renderer::Get()->Render();

			

			m_Window->OnUpdate();			
		}		

		Renderer::Get()->CleanUp();
	}

	void Application::PushLayer(Layer * layer)
		{
			m_LayerStack.PushLayer(layer);
			layer->OnAttach();
		}

		void Application::PushOverLay(Layer * overlay)
		{
			m_LayerStack.PushOverLay(overlay);
			overlay->OnAttach();
	}

	bool Application::OnWindowClosed(WindowCloseEvent & e)
	{
		m_Running = false;
		return true;
	}
}


