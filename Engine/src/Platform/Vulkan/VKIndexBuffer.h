#pragma once

#include "vulkan/vulkan.h"

namespace Engine {

	class VKIndexBuffer {

	public:
		VKIndexBuffer(VkDevice device, std::vector<uint32_t>& indices);
		~VKIndexBuffer();

		void Bind(VkCommandBuffer commandBuffer);
		void CleanUp(VkDevice device);

		inline const uint32_t Count()const { return m_Count; }

	private:
		unsigned int m_Count;

		VkBuffer m_Buffer;
		VkDeviceMemory m_Memory;
	};
}