#pragma once

#include "RendererAPI.h"
#include "Renderer.h"

namespace Engine {

	class RenderCommand
	{
	public :
		static void Init();		

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}

		

		inline static void BindGame()
		{

		}

	private:
		static RendererAPI* s_RendererAPI;
	};

}
