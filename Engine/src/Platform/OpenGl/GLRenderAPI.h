#pragma once

//#include "Engine/Renderer/RenderAPI.h"
//#include "Engine/ImGui/ImGuiLayer.h"
//
//namespace Engine {
//
//	class FrameBuffer;
//
//	class GLRenderAPI : public RenderAPI
//	{
//
//	public:
//		GLRenderAPI();
//		virtual ~GLRenderAPI();
//
//		virtual void Init() override;
//		virtual void Render() override;
//		virtual void CleanUp() override;
//
//		virtual void * GetSceneFrameBufferTexture() override;
//		virtual void * GetGameFrameBufferTexture() override;
//
//		static RenderAPI* Create();
//
//	private:
//		FrameBuffer* m_GameFrameBuffer;
//		FrameBuffer* m_SceneFrameBuffer;
//
//		ImGuiLayer* m_ImGuiLayer;
//		
//	};
//}