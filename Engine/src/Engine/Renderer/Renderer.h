#pragma once

#include "RenderCommand.h"

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



		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		static Renderer* s_Renderer;

		static glm::mat4 s_ProjectionMatrix;

	protected:
		glm::mat4 CreateProjectionMatrix();

	};
}