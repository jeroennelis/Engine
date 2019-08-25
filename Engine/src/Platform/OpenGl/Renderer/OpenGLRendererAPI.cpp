#include "enpch.h"

#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

#include "../Loader.h"

#include "Engine/Application.h"

namespace Engine {



	void OpenGLRendererAPI::Init()
	{
		EN_CORE_INFO("Initializing OpenGL Renderer");

		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glEnable(GL_BLEND));
		GLCall(glEnable(GL_DEPTH_TEST));
		SetClearColor({ 0.0, 0.0, 0.0, 1 });

		Loader::Create();
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}