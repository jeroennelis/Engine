#include "enpch.h"

#include "GLRenderAPI.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "Loader.h"
#include "Engine/Application.h"

namespace Engine {



	GLRenderAPI::GLRenderAPI()
	{
		EN_CORE_TRACE("init gl renderer");
		Init();
	}

	GLRenderAPI::~GLRenderAPI()
	{
	}

	RenderAPI* GLRenderAPI::Create()
	{
		return new GLRenderAPI();
	}

	void GLRenderAPI::CleanUp()
	{

	}

	void GLRenderAPI::Init()
	{	
		//Loader
		Loader::Create();

		//Create framebuffers
		m_GameFrameBuffer = new FrameBuffer(Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());
		m_SceneFrameBuffer = new FrameBuffer(Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());

		//init ImGui
		m_ImGuiLayer = new ImGuiLayer;
		Application::Get().PushOverLay(m_ImGuiLayer);

		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glEnable(GL_BLEND));
		GLCall(glEnable(GL_DEPTH_TEST));
	}

	void GLRenderAPI::Render()
	{
		m_GameFrameBuffer->Bind();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GLCall(glClearColor(0.5, 0, 0, 1));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		m_GameFrameBuffer->Unbind();

		m_SceneFrameBuffer->Bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GLCall(glClearColor(0, 0, 0.5, 1));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		for (Layer* layer : Application::Get().GetLayerStack())
			layer->OnUpdate();

		m_SceneFrameBuffer->Unbind();

		m_ImGuiLayer->Begin();
		for (Layer* layer : Application::Get().GetLayerStack())
			layer->OnImGuiRender();
		m_ImGuiLayer->End();
	}

	void * GLRenderAPI::GetSceneFrameBufferTexture()
	{
		return (void*)(UINT_PTR)m_SceneFrameBuffer->GetTexture();
	}

	void * GLRenderAPI::GetGameFrameBufferTexture()
	{
		return (void*)(UINT_PTR)m_GameFrameBuffer->GetTexture();
	}
}