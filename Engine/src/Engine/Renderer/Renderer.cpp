#include "enpch.h"

#include "Renderer.h"

#include "Platform/OpenGl/OpenGLRenderer.h"
#include "Platform/Vulkan/VulkanRenderer.h"

namespace Engine {

	//Hard coded at the moment
	RendererAPItest Renderer::s_RendererAPI = RendererAPItest::OpenGL;
	Renderer* Renderer::s_Renderer = nullptr;

	void Renderer::Create(RendererAPItest api)
	{
		s_RendererAPI = api;
		switch (api)
		{
		case RendererAPItest::None: 
			EN_CORE_ASSERT(false, "RendererAPI::NONE currently not supported"); 
			s_Renderer = nullptr; 
			return;

		case RendererAPItest::OpenGL: 
			s_Renderer = new OpenGLRenderer();
			break;

		case RendererAPItest::Vulkan: 
			s_Renderer = new VulkanRenderer();
			break;
		}
	}
}