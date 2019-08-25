#include "enpch.h"

#include "Renderer.h"

#include "Platform/OpenGl/Renderer/OpenGLRenderer.h"
#include "Platform/Vulkan/VulkanRenderer.h"
#include "Platform/OpenVR/OpenGL/OpenVR_OpenGLRenderer.h"

namespace Engine {

	//Hard coded at the moment
	
	Renderer* Renderer::s_Renderer = nullptr;
	glm::mat4 Renderer::s_ProjectionMatrix(1.0);
	glm::mat4 Renderer::s_ViewMatrix(1.0);

	void Renderer::Init()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			EN_CORE_ASSERT(false, "RendererAPI::NONE currently not supported");
			break;

		case RendererAPI::API::OpenGL:
			s_Renderer = new OpenGLRenderer();
			break;

		case RendererAPI::API::Vulkan:
			s_Renderer = new VulkanRenderer();
			break;

		case RendererAPI::API::OpenVR_OpenGL: 
			s_Renderer = new OpenGLRenderer();
			break;
		}
		RenderCommand::Init();
		s_Renderer->Initialize();
	}

	void Renderer::BeginScene(Camera* cam)
	{
		s_ProjectionMatrix = cam->GetProjectionMatrix();
		s_ViewMatrix = cam->GetViewMatrix();
	}

	void Renderer::EndScene()
	{
		//ToDo in Future
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}