#include "enpch.h"

#include "VertexArray.h"
#include "Renderer.h"

#include "Platform/OpenGl/OpenGLVertexArray.h"

namespace Engine {
	
	
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPItest::None: EN_CORE_ASSERT(false, "RendererAPI::NONE currently not supported"); return nullptr;

			case RendererAPItest::OpenGL: return new OpenGLVertexArray();

			//case RendererAPItest::Vulkan:return new VulkanVertexArray();
		}

		EN_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}