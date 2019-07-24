#include "enpch.h"
#include "OpenGLRenderer.h"
#include "FrameBuffer.h"
#include "Engine/Application.h"
#include "Loader.h"

#include "MeshRenderer.h"

namespace Engine {

	OpenGLRenderer::OpenGLRenderer()
	{
	}

	OpenGLRenderer::~OpenGLRenderer()
	{
	}

	bool OpenGLRenderer::Init()
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

		return true;
	}

	void OpenGLRenderer::Render()
	{
		SetProjectionMatrix(CreateProjectionMatrix());
		RenderGame();

		RenderScene();
		
		
		RenderImGui();

		
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

	void OpenGLRenderer::RenderScene()
	{
		m_SceneFrameBuffer->Bind();

		RenderFrame();

		m_SceneFrameBuffer->Unbind();
	}

	void OpenGLRenderer::RenderGame()
	{
		m_GameFrameBuffer->Bind();
		RenderCommand::SetClearColor({ 0.5, 0, 0, 1 });
		RenderCommand::Clear();
		m_GameFrameBuffer->Unbind();
	}

	void OpenGLRenderer::RenderFrame()
	{
		RenderCommand::SetClearColor({ 0.0, 0, 0.0, 1 });
		RenderCommand::Clear();

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		Renderer::BeginScene();
		
		


		

		if (Scene::Current()->SelectedGameObject() != nullptr && Scene::Current()->SelectedGameObject()->GetComponent<MeshRenderer>() != nullptr)
		{
			//render selected obj

			//glEnable(GL_STENCIL_TEST);
			//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

			//glStencilMask(0xFF); // enable writing to the stencil buffer
			//glClear(GL_STENCIL_BUFFER_BIT); 

			//glStencilFunc(GL_ALWAYS, 1, 0xFF); // all fragments should update the stencil buffer



			Scene::Current()->SelectedGameObject()->GetComponent<MeshRenderer>()->Draw();

			/*glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
			glStencilMask(0x00);*/

			Scene::Current()->SelectedGameObject()->GetComponent<MeshRenderer>()->DrawOutline();
			/*glStencilMask(0xFF);
			glEnable(GL_DEPTH_TEST);*/


		}

		glDisable(GL_STENCIL_TEST);

		{
			for (Layer* layer : Application::Get().GetLayerStack())
				layer->OnRender();
		}

		Renderer::EndScene();
	}

	void OpenGLRenderer::RenderImGui()
	{
		m_ImGuiLayer->Begin();
		for (Layer* layer : Application::Get().GetLayerStack())
			layer->OnImGuiRender();
		m_ImGuiLayer->End();
	}
}
