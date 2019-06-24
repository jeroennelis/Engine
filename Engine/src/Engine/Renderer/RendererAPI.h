#pragma once

#include "VertexArray.h"

namespace Engine {

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1, Vulkan = 2, OpenVR_OpenGL = 3
		};

	public:
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_API; }
		inline static void SetAPI(const API api) { s_API = api; }

	private:
		static API s_API;
	};
}