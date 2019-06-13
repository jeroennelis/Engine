#include "enpch.h"

#include "Buffer.h"
#include "Renderer.h"

#include "Platform/OpenGl/OpenGLBuffer.h"
#include "Platform/Vulkan/VulkanBuffer.h"

namespace Engine {
	
	/*VertexArrayTemp* VertexArrayTemp::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPItest::None: EN_CORE_ASSERT(false, "RendererAPI::NONE currently not supported"); return nullptr;

		case RendererAPItest::OpenGL: return new OpenGLVertexArrayTemp();
		}

		EN_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}*/

	VertexBuffer* VertexBuffer::Create(const void* data, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPItest::None: EN_CORE_ASSERT(false, "RendererAPI::NONE currently not supported"); return nullptr;

			case RendererAPItest::OpenGL: return new OpenGLVertexBuffer(data, size);

			case RendererAPItest::Vulkan:return new VulkanVertexBuffer(data, size);
		}

		EN_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPItest::None: EN_CORE_ASSERT(false, "RendererAPI::NONE currently not supported"); return nullptr;

		case RendererAPItest::OpenGL: return new OpenGLIndexBuffer(indices, count);

		case RendererAPItest::Vulkan:return new VulkanIndexBuffer(indices, count);
		}

		EN_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}