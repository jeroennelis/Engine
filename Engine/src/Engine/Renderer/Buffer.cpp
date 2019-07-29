#include "enpch.h"

#include "Buffer.h"
#include "Renderer.h"

#include "Platform/OpenGl/Renderer/OpenGLBuffer.h"
#include "Platform/Vulkan/VulkanBuffer.h"

namespace Engine {
	
	VertexBuffer* VertexBuffer::Create(const void* data, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: EN_CORE_ASSERT(false, "RendererAPI::NONE currently not supported"); return nullptr;

			case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(data, size);

			case RendererAPI::API::Vulkan:return new VulkanVertexBuffer(data, size);

			case RendererAPI::API::OpenVR_OpenGL: return new OpenGLVertexBuffer(data, size);
		}

		EN_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: EN_CORE_ASSERT(false, "RendererAPI::NONE currently not supported"); return nullptr;

			case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, count);

			case RendererAPI::API::Vulkan:return new VulkanIndexBuffer(indices, count);

			case RendererAPI::API::OpenVR_OpenGL: return new OpenGLIndexBuffer(indices, count);
		}

		EN_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}