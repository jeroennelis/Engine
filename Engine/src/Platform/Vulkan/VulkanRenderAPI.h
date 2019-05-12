#pragma once

#include "Engine/Renderer/RenderAPI.h"
#include "vulkan/vulkan.h"
#include "Engine/Application.h"

#define DISABLE_VK_LAYER_VALVE_steam_overlay_1 1
#define GLFW_INCLUDE_VULCAN

#include <vector>
#include <algorithm>
#include <fstream>
#include <limits>
#include <ctime>
#include <glm/glm.hpp>
#include <array>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>

#include <unordered_map>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include "VKVertexBuffer.h"
#include "VKIndexBuffer.h"



namespace Engine {

	struct VulkanVertex {
		glm::vec3 pos;
		glm::vec3 normals;
		glm::vec3 color;
		glm::vec2 texCoord;

		inline bool operator==(const VulkanVertex&other) const
		{
			return pos == other.pos && normals == other.normals && color == other.color && texCoord == other.texCoord;
		}

		static VkVertexInputBindingDescription getBindingDescription();
		static std::array<VkVertexInputAttributeDescription, 4> GetAttributeDescriptions();

		
	};



	struct UniformBufferObject {
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 proj;
	};

	struct QueueFamilyIndices {
		int graphicsFamily = -1;
		int presentFamily = -1;

		bool isComplete()
		{
			return graphicsFamily >= 0 && presentFamily >= 0;
		}
	};

	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};


	class VulkanRenderAPI : public RenderAPI
	{

	public:
		VulkanRenderAPI();
		virtual ~VulkanRenderAPI();

		virtual void Init() override;
		virtual void CleanUp() override;
		virtual void Render() override;

		static RenderAPI* Create();

		static inline const VkDevice GetDevice() { return device; }
		static inline const VkPhysicalDevice GetPhysicalDevice() { return physicalDevice; }

		// Inherited via RenderAPI
		virtual void * GetSceneFrameBufferTexture() override;
		virtual void * GetGameFrameBufferTexture() override;

		static void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
		static void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);


		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData);

	private:
		void InitVulkan();

		void CreateInstance();
		void SetupDebugCallback();
		void CreateSurface();
		void PickPhysicalDevice();
		void CreateLogicalDevice();
		void CreateSwapChain();
		void CreateImageViews();
		void CreateRenderPass();
		void CreateDescriptorSetLayout();
		void CreateGraphicsPipeline();
		void CreateFrameBuffers();
		void CreateCommandPool();
		void CreateDepthResources();
		void CreateTextureImage(const std::string& file_pat);
		void CreateTextureImageView();
		void CreateTextureSampler();
		void LoadModel(const std::string& file_path);
		void CreateUniformBuffers();
		void CreateUniformBuffer(VkDeviceSize& bufferSize);
		void CreateDescriptorPools();
		void CreateDescriptorPool(uint32_t index);
		void CreateDescriptorSets();
		void CreateDescriptorSet(uint32_t index);
		void CreateCommandBuffers();
		void CreateSyncObjects();

		void UpdateUniformBuffer(uint32_t index);

		void CleanUpSwapChain();
		void RecreateSwapChain();

		

		//validation layers
		bool CheckValidationLayerSupport();
		const std::vector<const char*> validationLayers = {
			"VK_LAYER_LUNARG_standard_validation"
		};

		//extentions
		std::vector<const char*> getRequiredExtension();

		//physical device
		bool IsDeviceSuitable(VkPhysicalDevice device);
		QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
		bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
		const std::vector<const char*> deviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};
		SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);

		//swap chain settings
		VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

		VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

		VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
		VkFormat FindDepthFormat();

		//shader
		static std::vector<char> ReadFile(const std::string& fileName);
		VkShaderModule CreateShaderModule(const std::vector<char>& code);

		void CreateImage(uint32_t width, uint32_t height, VkFormat format,
			VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties,
			VkImage& image, VkDeviceMemory& imageMemory);

		void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
		void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

		static VkCommandBuffer BeginSingleTimeCommands();
		static void EndSingleTimeCommands(VkCommandBuffer commandBuffer);
		static uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

		void DestroyDebugUtilsMessengerEXT(VkInstance instance,
			VkDebugUtilsMessengerEXT callback, const
			VkAllocationCallbacks* pAllocator);

		VkInstance instance;
		VkDebugUtilsMessengerEXT callback;
		VkSurfaceKHR surface;
		static VkPhysicalDevice physicalDevice;
		static VkDevice device;									//logical device
		static VkQueue graphicsQueue;
		VkQueue presentQueue;
		VkSwapchainKHR swapChain;
		std::vector<VkImage> swapChainImages;
		VkFormat swapChainImageFormat;
		VkExtent2D swapChainExtent;
		VkRenderPass renderPass;
		VkPipelineLayout pipelineLayout;
		VkPipeline graphicsPipeline;
		static VkCommandPool commandPool;

		std::vector<VKVertexBuffer> vertexBuffers;
		std::vector<VKIndexBuffer> indexBuffers;

		std::vector<int> nrOfindices;

		std::vector<VkBuffer> uniformBuffers;
		std::vector<VkDeviceMemory> uniformBuffersMemory;

		std::vector<VkImageView> swapChainImageViews;
		std::vector<VkFramebuffer> swapChainFrameBuffers;
		std::vector<VkCommandBuffer> commandBuffers;

		std::vector<VkSemaphore> imageavailableSemaphores;
		std::vector<VkSemaphore> renderFinishedSemaphores;
		std::vector<VkFence> inFlightFences;

		VkDescriptorSetLayout descriptorSetLayout;
		std::vector<VkDescriptorPool> descriptorPools;
		std::vector<VkDescriptorSet> descriptorSets;

		std::array<VkWriteDescriptorSet, 4> descriptorWrites;

		VkImage textureImage;
		VkDeviceMemory textureImageMemory;
		VkImageView textureImageView;
		VkSampler textureSampler;

		VkImage depthImage;
		VkDeviceMemory depthImageMemory;
		VkImageView depthImageView;

		size_t currentFrame = 0;

		bool frameBufferResized = false;

		const int MAX_FRAMES_IN_FLIGHT = 2;

#ifdef NDEBUG
		const bool enableValidationLayers = false;
#else
		const bool enableValidationLayers = true;
#endif
	};
}

namespace std {
	template<> struct hash<Engine::VulkanVertex> {
		size_t operator()(Engine::VulkanVertex const& vertex) const {
			return ((hash<glm::vec3>()(vertex.pos) ^
				(hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^
				(hash<glm::vec2>()(vertex.texCoord) << 1);
		}
	};
}
