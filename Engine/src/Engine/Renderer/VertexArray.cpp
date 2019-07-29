#include "enpch.h"

#include "VertexArray.h"
#include "Renderer.h"

#include "Platform/OpenGl/Renderer/OpenGLVertexArray.h"

namespace Engine {
	
	
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: EN_CORE_ASSERT(false, "RendererAPI::NONE currently not supported"); return nullptr;

		case RendererAPI::API::OpenGL: return new OpenGLVertexArray();

			//case RendererAPItest::Vulkan:return new VulkanVertexArray();

		case RendererAPI::API::OpenVR_OpenGL: return new OpenGLVertexArray();
		}

		EN_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}