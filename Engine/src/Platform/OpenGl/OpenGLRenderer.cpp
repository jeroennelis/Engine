#include "enpch.h"
#include "OpenGLRenderer.h"
#include "FrameBuffer.h"
#include "Engine/Application.h"
#include "Loader.h"

namespace Engine {

	OpenGLRenderer::OpenGLRenderer()
	{
	}

	OpenGLRenderer::~OpenGLRenderer()
	{
	}

	void OpenGLRenderer::Init()
	{
		EN_CORE_INFO("Initializing OpenGL Renderer");
		//Loader
		Loader::Create();

		//Create framebuffers
		int width = Application::Get().GetWindow().GetWidth();
		int height = Application::Get().GetWindow().GetHeight();

		m_GameFrameBuffer = new FrameBuffer(Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());
		m_SceneFrameBuffer = new FrameBuffer(Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());

		//init ImGui
		m_ImGuiLayer = new ImGuiLayer;
		Application::Get().PushOverLay(m_ImGuiLayer);

		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glEnable(GL_BLEND));
		GLCall(glEnable(GL_DEPTH_TEST));
	}

	void OpenGLRenderer::Render()
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
			layer->OnRender();

		m_SceneFrameBuffer->Unbind();

		m_ImGuiLayer->Begin();
		for (Layer* layer : Application::Get().GetLayerStack())
			layer->OnImGuiRender();
		m_ImGuiLayer->End();
	}

	void OpenGLRenderer::CleanUp()
	{
	}

	void* OpenGLRenderer::GetSceneFrameBufferTexture()
	{
		return (void*)(UINT_PTR)m_SceneFrameBuffer->GetTexture();
	}

	void* OpenGLRenderer::GetGameFrameBufferTexture()
	{
		return (void*)(UINT_PTR)m_GameFrameBuffer->GetTexture();
	}
}
