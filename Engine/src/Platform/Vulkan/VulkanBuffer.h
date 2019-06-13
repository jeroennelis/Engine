#pragma once

#include "Engine/Renderer/Buffer.h"
#include "vulkan/vulkan.h"

namespace Engine {

	class VulkanVertexBuffer : public VertexBuffer
	{

	public:
		VulkanVertexBuffer(const void* data, uint32_t size  );
		virtual ~VulkanVertexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
	private:
		VkBuffer m_Buffer;
		VkDeviceMemory m_Memory;

		BufferLayout m_Layout;

	};

	class VulkanIndexBuffer : public IndexBuffer
	{

	public:
		VulkanIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~VulkanIndexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		inline uint32_t GetCount() const override { return m_Count; }

	private:
		uint32_t m_Count;
		VkBuffer m_Buffer;
		VkDeviceMemory m_Memory;
	};
}
