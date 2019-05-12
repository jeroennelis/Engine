#include "enpch.h"

#include "VKVertexBuffer.h"
#include "VulkanRenderAPI.h"

namespace Engine {

	VKVertexBuffer::VKVertexBuffer(VkDevice device, std::vector<VulkanVertex>& vertices)
	{
		VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;

		VulkanRenderAPI::CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

		void* data;
		vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, vertices.data(), (size_t)bufferSize);
		vkUnmapMemory(device, stagingBufferMemory);

		VulkanRenderAPI::CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_Buffer, m_Memory);

		VulkanRenderAPI::CopyBuffer(stagingBuffer, m_Buffer, bufferSize);

		vkDestroyBuffer(device, stagingBuffer, nullptr);
		vkFreeMemory(device, stagingBufferMemory, nullptr);

		//p177: max nr of allocations
	}

	VKVertexBuffer::~VKVertexBuffer()
	{
	}

	void VKVertexBuffer::Bind(VkCommandBuffer commandBuffer)
	{
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, static_cast<uint32_t>(1), &m_Buffer, offsets);
	}

	void VKVertexBuffer::CleanUp(VkDevice device)
	{
		vkDestroyBuffer(device, m_Buffer, nullptr);
		vkFreeMemory(device, m_Memory, nullptr);
	}
}