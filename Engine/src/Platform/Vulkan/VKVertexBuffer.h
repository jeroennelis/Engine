#pragma once
#include "vulkan/vulkan.h"

namespace Engine {

	struct VulkanVertex;

	class VKVertexBuffer {

	public:
		VKVertexBuffer(VkDevice device, std::vector<VulkanVertex>& vertices);
		~VKVertexBuffer();

		void Bind(VkCommandBuffer commandBuffer);
		void CleanUp(VkDevice device);

	private:
		VkBuffer m_Buffer;
		VkDeviceMemory m_Memory;
	};
}
