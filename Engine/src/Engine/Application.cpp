#include "enpch.h"
#include "Application.h"

#include "Engine/Log.h"

#include <Glad/glad.h>

#include <openvr.h>
#include "Components/TestComponent.h"
#include "GameObject.h"
#include "Engine/Logic/Scene.h"
#include "Maths/src/Vector2.h"
#include "Components/Transform.h"

#include "Input.h"

#include "Platform/OpenGl/FrameBuffer.h"

namespace Engine {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()	
	{
		EN_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_GameFrameBuffer = new FrameBuffer(GetWindow().GetWidth(), GetWindow().GetHeight());

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
		TestComponent test;
		std::shared_ptr<Transform> transform = std::make_shared<Transform>();
		std::shared_ptr<Transform> transform2 = std::make_shared<Transform>();
		transform->Position.x = 5;
		transform->Position.z = -2;
		std::shared_ptr<GameObject> testObject = std::make_shared<GameObject>("TestObject1");
		std::shared_ptr<GameObject> testObject2 = std::make_shared<GameObject>("TestObject2");
		std::shared_ptr<GameObject> testObject3 = std::make_shared<GameObject>("TestObject3");
		std::shared_ptr<GameObject> testObject4 = std::make_shared<GameObject>("TestObject4");
		std::shared_ptr<GameObject> testObject5 = std::make_shared<GameObject>("TestObject5");
		std::shared_ptr<GameObject> testObject6 = std::make_shared<GameObject>("TestObject6");
		std::shared_ptr<GameObject> testObject7 = std::make_shared<GameObject>("TestObject7");
		testObject->AddComponent(transform);
		testObject4->AddComponent(transform2);
		testObject->GetComponent<TestComponent>();

		Scene::Current()->AddGameObject(testObject);
		Scene::Current()->AddGameObject(testObject2);
		testObject->AddChild(testObject3);
		testObject->AddChild(testObject6);
		testObject3->AddChild(testObject4);
		testObject3->AddChild(testObject7);
		testObject2->AddChild(testObject5);

		Scene scene("scene 2");
		//Scene::SetCurrent(&scene);

		XMLReader::ReadFile("test.xml");
		

		while (m_Running)
		{
			m_GameFrameBuffer->Bind();
			glClearColor(0, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_GameFrameBuffer->Unbind();
			glClearColor(1, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			
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


