#include  "enpch.h" 
#include  "Application.h" 

#include "Input.h" 

#include "Logic/LogicLayer.h"

namespace Engine {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;


	glm::mat4 CreateProjectionMatrix();

	Application::Application()
	{
		EN_CORE_ASSERT(!s_Instance, Application already exists!);
		s_Instance = this;

		RENDER_API api = GL;


		m_Window = std::unique_ptr<Window>(Window::Create(api));
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		if(api == VULKAN)
			m_RenderAPI = std::unique_ptr<RenderAPI>(VulkanRenderAPI::Create());
		else if (api == GL)
			m_RenderAPI = std::unique_ptr<RenderAPI>(GLRenderAPI::Create());
		
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

			m_RenderAPI->Render();

			m_Window->OnUpdate();

			

			
		}		
		m_RenderAPI->CleanUp();
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
	glm::mat4 CreateProjectionMatrix()
	{
		float aspectRatio = (float)Application::Get().GetWindow().GetWidth() / (float)Application::Get().GetWindow().GetHeight();
		//fov
		float y_scale = (float)((1.0f / glm::tan(glm::radians(110 / 2.0f))) * aspectRatio);
		float x_scale = y_scale / aspectRatio;
		float frustum_length = 1000 - 0.1f;

		glm::mat4 projectionMatrix = glm::mat4();
		projectionMatrix[0][0] = x_scale;
		projectionMatrix[1][1] = y_scale;
		projectionMatrix[2][2] = -((1000 + 0.1f) / frustum_length);
		projectionMatrix[2][3] = -1;
		projectionMatrix[3][2] = -((2 * 0.1f * 1000) / frustum_length);
		projectionMatrix[3][3] = 0;

		return projectionMatrix;
	}
}


