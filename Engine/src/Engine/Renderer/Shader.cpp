#include "enpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGl/Renderer/OpenGLShader.h"

namespace Engine {

	Shader* Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: EN_CORE_ASSERT(false, "RendererAPI::NONE currently not supported"); return nullptr;

		case RendererAPI::API::OpenGL: return new OpenGLShader(filepath);

			//case RendererAPItest::Vulkan:return new VulkanVertexArray();

		case RendererAPI::API::OpenVR_OpenGL: return new OpenGLShader(filepath);
		}

		EN_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}

