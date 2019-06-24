#include "enpch.h"

#include "Renderer.h"

#include "Platform/OpenGl/OpenGLRenderer.h"
#include "Platform/Vulkan/VulkanRenderer.h"
#include "Platform/OpenVR/OpenGL/OpenVR_OpenGLRenderer.h"

namespace Engine {

	//Hard coded at the moment
	
	Renderer* Renderer::s_Renderer = nullptr;

	glm::mat4 Renderer::s_ProjectionMatrix = glm::mat4();

	void Renderer::Create()
	{
		
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: 
			EN_CORE_ASSERT(false, "RendererAPI::NONE currently not supported"); 
			s_Renderer = nullptr; 
			return;

		case RendererAPI::API::OpenGL: 
			s_Renderer = new OpenGLRenderer();
			s_Renderer->Init();
			break;

		case RendererAPI::API::Vulkan: 
			s_Renderer = new VulkanRenderer();
			s_Renderer->Init();
			break;

		case RendererAPI::API::OpenVR_OpenGL:
			s_Renderer = new OpenVR_OpenGLRenderer();
			if (!s_Renderer->Init())
			{
				RendererAPI::SetAPI(RendererAPI::API::OpenGL);
				s_Renderer = new OpenGLRenderer();
				s_Renderer->Init();
			}
			break;
		}
	}

	glm::mat4 Renderer::CreateProjectionMatrix()
	{
		float aspectRatio = (float)Application::Get().GetWindow().GetWidth() / (float)Application::Get().GetWindow().GetHeight();
		//fov
		float y_scale = (float)((1.0f / glm::tan(glm::radians(110 / 2.0f))) * aspectRatio);
		float x_scale = y_scale / aspectRatio;
		float frustum_length = 1000 - 0.1f;

		glm::mat4 projectionMatrix = glm::mat4();
		projectionMatrix[0][0] = x_scale;
		projectionMatrix[1][1] = y_scale;
		projectionMatrix[2][2] = -((1000 + 0.1f) / frustum_length);
		projectionMatrix[2][3] = -1;
		projectionMatrix[3][2] = -((2 * 0.1f * 1000) / frustum_length);
		projectionMatrix[3][3] = 0;

		return projectionMatrix;
	}



	void Renderer::BeginScene()
	{
		//ToDo in Future
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