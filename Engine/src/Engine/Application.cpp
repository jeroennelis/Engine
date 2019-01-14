#include "enpch.h"
#include "Application.h"

#include "Engine/Log.h"

#include <Glad/glad.h>

#include <openvr.h>
#include "Physics/Test.h"
#include "Components/TestComponent.h"
#include "GameObject.h"

namespace Engine {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		EN_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		
		unsigned int id;
		glGenVertexArrays(1, &id);
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
			(*--it)->OnEvent(e);
			if (e.Handled())
				break;
		}
	}

	

	void Application::Run()
	{
		TestComponent test;
		EN_CORE_INFO(test.ID());
		EN_CORE_INFO(test.Name());

		GameObject testObject("TestObject");
		testObject.AddComponent(&test);
		testObject.GetComponent<TestComponent>();

		TestComponent* temp = testObject.GetComponent<TestComponent>();
		;
		EN_CORE_INFO(temp->Name());
		while (m_Running)
		{
			glClearColor(1, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			
			
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}

		
		
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


