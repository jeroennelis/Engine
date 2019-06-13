#include "enpch.h"

#include "VulkanBuffer.h"
#include "VulkanRenderer.h"

namespace Engine {

	///////////////////////////////////////////////////
	// OpenGL VertexBuffer ////////////////////////////
	///////////////////////////////////////////////////

	VulkanVertexBuffer::VulkanVertexBuffer(const void* data, uint32_t size)
	{
		VkDeviceSize bufferSize = size;

		VkDevice device = VulkanRenderer::GetDevice();

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;

		VulkanRenderer::CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

		void* bufferData;
		vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &bufferData);
		memcpy(bufferData, data, (size_t)bufferSize);
		vkUnmapMemory(device, stagingBufferMemory);

		VulkanRenderer::CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_Buffer, m_Memory);

		VulkanRenderer::CopyBuffer(stagingBuffer, m_Buffer, bufferSize);

		vkDestroyBuffer(device, stagingBuffer, nullptr);
		vkFreeMemory(device, stagingBufferMemory, nullptr);

		//p177: max nr of allocations
	}
	
	VulkanVertexBuffer::~VulkanVertexBuffer()
	{
		vkDestroyBuffer(VulkanRenderer::GetDevice(), m_Buffer, nullptr);
		vkFreeMemory(VulkanRenderer::GetDevice(), m_Memory, nullptr);
	}

	void VulkanVertexBuffer::Bind() const
	{
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(VulkanRenderer::GetCurrentCommandBuffer(), 0, static_cast<uint32_t>(1), &m_Buffer, offsets);
	}

	void VulkanVertexBuffer::UnBind() const
	{
	}

	


	///////////////////////////////////////////////////
	// OpenGL IndexBuffer /////////////////////////////
	///////////////////////////////////////////////////

	VulkanIndexBuffer::VulkanIndexBuffer(uint32_t* indices, uint32_t count)
		:m_Count(count)
	{
		VkDeviceSize bufferSize = sizeof(uint32_t) * count;

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;
		VulkanRenderer::CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

		VkDevice device = VulkanRenderer::GetDevice();

		void* data;
		vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, indices, (size_t)bufferSize);
		vkUnmapMemory(device, stagingBufferMemory);

		VulkanRenderer::CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_Buffer, m_Memory);

		VulkanRenderer::CopyBuffer(stagingBuffer, m_Buffer, bufferSize);

		vkDestroyBuffer(device, stagingBuffer, nullptr);
		vkFreeMemory(device, stagingBufferMemory, nullptr);
	}

	VulkanIndexBuffer::~VulkanIndexBuffer()
	{
		vkDestroyBuffer(VulkanRenderer::GetDevice(), m_Buffer, nullptr);
		vkFreeMemory(VulkanRenderer::GetDevice(), m_Memory, nullptr);
	}


	void VulkanIndexBuffer::Bind() const
	{
		vkCmdBindIndexBuffer(VulkanRenderer::GetCurrentCommandBuffer(), m_Buffer, 0, VK_INDEX_TYPE_UINT32);
	}

	void VulkanIndexBuffer::UnBind() const
	{
	}
}