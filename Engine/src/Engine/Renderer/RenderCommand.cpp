#include "enpch.h"

#include "RenderCommand.h"
#include "Platform/OpenGl/Renderer/OpenGLRendererAPI.h"
#include "Platform/Vulkan/VulkanRendererAPI.h"

namespace Engine {
	RendererAPI* RenderCommand::s_RendererAPI = nullptr;

	void RenderCommand::Init()
	{
		
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: 
			EN_CORE_ASSERT(false, "RendererAPI::NONE currently not supported");
			break;

		case RendererAPI::API::OpenGL: 
			s_RendererAPI = new OpenGLRendererAPI(); 
			break;

		case RendererAPI::API::Vulkan: s_RendererAPI = new VulkanRendererAPI(); 
			break;

		case RendererAPI::API::OpenVR_OpenGL: s_RendererAPI = new OpenGLRendererAPI();

		}
		s_RendererAPI->Init();
		
	}

}