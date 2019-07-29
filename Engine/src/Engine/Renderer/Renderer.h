#pragma once

#include "RenderCommand.h"

#include "Engine/Components/Camera.h"

namespace Engine {


	class Renderer
	{
	public:
		

		static void Create();
		inline static Renderer* Get() { return s_Renderer; }
		virtual bool Init() = 0;

		virtual void Render() = 0;
		virtual void CleanUp() = 0;

		virtual void* GetSceneFrameBufferTexture() = 0;
		virtual void* GetGameFrameBufferTexture() = 0;

		inline static void SetProjectionMatrix(const glm::mat4& projectionMatrix) { s_ProjectionMatrix = projectionMatrix; }
		inline static const glm::mat4& GetProjectionMatrix() { return s_ProjectionMatrix; }

		inline static void SetViewMatrix(const glm::mat4& viewMatrix) { s_ViewMatrix = viewMatrix; }
		inline static const glm::mat4& GetViewMatrix() { return s_ViewMatrix; }

		inline static void SetTransforms(Camera* cam) { s_ProjectionMatrix = cam->GetProjectionMatrix(); s_ViewMatrix = cam->GetViewMatrix(); }

		static void BeginScene(Camera* cam);
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		static Renderer* s_Renderer;

		static glm::mat4 s_ProjectionMatrix;
		static glm::mat4 s_ViewMatrix;

	};
}