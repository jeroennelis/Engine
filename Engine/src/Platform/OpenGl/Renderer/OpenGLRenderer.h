#pragma once

#include "Engine/Renderer/Renderer.h"
#include "Engine/ImGui/ImGuiLayer.h"



namespace Engine {

	class FrameBuffer;

	class OpenGLRenderer : public Renderer
	{
	public:
		OpenGLRenderer();
		virtual ~OpenGLRenderer();

		bool Initialize() override;
		virtual void Render() override;
		virtual void CleanUp() override;

		virtual void* GetSceneFrameBufferTexture() override;
		virtual void* GetGameFrameBufferTexture() override;

	private:
		FrameBuffer* m_GameFrameBuffer;
		FrameBuffer* m_SceneFrameBuffer;

		ImGuiLayer* m_ImGuiLayer;

	protected:
		void RenderScene();

		void RenderGame();

		void RenderFrame();

		void RenderImGui();
	};
}