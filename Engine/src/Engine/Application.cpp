#include  "enpch.h" 
#include  "Application.h" 

#include  "Engine/Log.h" 

#include <Glad/glad.h>""

#include <openvr.h>
#include "Components/TestComponent.h" 
#include "GameObject.h"
#include "Engine/Logic/Scene.h" 
#include "Maths/src/Vector2.h" 
#include "Components/Transform.h" 

#include "Input.h" 

#include "Platform/OpenGl/FrameBuffer.h" 
#include <fstream>

#include "Platform/OpenGl/Renderer.h"
#include "Platform/OpenGl/VertexBuffer.h"
#include "Platform/OpenGl/IndexBuffer.h"
#include "Platform/OpenGl/VertexArray.h"
#include "Platform/OpenGl/Shader.h"
#include "Platform/OpenGl/VertexBufferLayout.h"

namespace Engine {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		EN_CORE_ASSERT(!s_Instance, Application already exists!);
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_GameFrameBuffer = new FrameBuffer(GetWindow().GetWidth(), GetWindow().GetHeight());
		m_SceneFrameBuffer = new FrameBuffer(GetWindow().GetWidth(), GetWindow().GetHeight());
		m_ImGuiLayer = new ImGuiLayer;
		PushOverLay(m_ImGuiLayer);
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
		

//------------ Temp rendering------------//
		float positions[] = {
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f,  0.5f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		VertexArray va;
		VertexBuffer vb(positions, 4 * 2 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);
		
		IndexBuffer ib(indices, 6);

		Shader shader("../Engine/res/shaders/basic.shader");
		shader.Bind();
		shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

		va.UnBind();
		shader.UnBind();
		vb.UnBind();
		ib.UnBind();

		Renderer renderer;

		while (m_Running)
		{
			

			m_GameFrameBuffer->Bind();
			GLCall(glClearColor(0, 0, 0.5, 1));
			renderer.Clear();
			renderer.Draw(va, ib, shader);
			m_GameFrameBuffer->Unbind();
			
			m_SceneFrameBuffer->Bind();
			GLCall(glClearColor(0.5, 0, 0, 1));
			renderer.Clear();
			renderer.Draw(va, ib, shader);
			m_SceneFrameBuffer->Unbind();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

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


