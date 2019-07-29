#include  "enpch.h" 
#include  "Application.h" 

#include "Input.h" 

#include "Logic/LogicLayer.h"
#include "Renderer/Renderer.h"
#include "Renderer/Buffer.h"
#include "image.h"
#include "Platform/OpenGl/Materials/OpenGLTerrainMaterial.h"
#include "Platform/OpenGl/Loader.h"
#include "Platform/OpenGl/TerrainRenderer.h"
#include "Platform/OpenGl/Terrain.h"


namespace Engine {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr; 


	Application::Application()
	{
		EN_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create(Renderer::GetAPI()));
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_Window->SetVSync(false );

		
		Renderer::Create();
		

		//RTTexture = new GLTexture();
				
		PushLayer(new LogicLayer());

		OpenGLTerrainMaterial* mat = new OpenGLTerrainMaterial(Loader::Get()->GetShader("terrain"), "terrainmaterial");

		std::shared_ptr<GameObject> go = std::make_shared<GameObject>("terrain");		//TODO
		Transform* transform = go->GetComponent<Transform>();
		transform->Position = glm::vec3(0, 0.0, -100.0);
		Terrain* terrain = new Terrain(0, 0, "../Engine/res/textures/heightMap.png");

		GLTexture* BGTexture = new GLTexture("../Engine/res/textures/grass.png");
		GLTexture* rTexture = new GLTexture("../Engine/res/textures/mud.png");
		GLTexture* gTexture = new GLTexture("../Engine/res/textures/grassFlowers.png");
		GLTexture* bTexture = new GLTexture("../Engine/res/textures/path.png");
		GLTexture* blendMap = new GLTexture("../Engine/res/textures/blendMap.png");

		mat->SetTextures(BGTexture, rTexture, gTexture, bTexture, blendMap);
		std::shared_ptr<TerrainRenderer> meshRenderer = std::make_shared<TerrainRenderer>(mat, terrain->GetModel(), transform);  //TODO: mem leak
		go->AddComponent(meshRenderer);
		Scene::Current()->AddGameObject(go);
		Scene::Current()->AddCube();
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


