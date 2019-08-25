#include "enpch.h"
#include "IconRenderer.h"
#include "Engine/Renderer/Renderer.h"

namespace Engine {

	IconRenderer::IconRenderer(OpenGLMaterial* material, Transform* transform)
		:RenderComponent("IconRenderer"), m_Material(material), m_Transform(transform)
	{
		float data[] = { -0.5f, 0.5f, 0.0f, 0.0f,
						 -0.5f,-0.5f, 0.0f, 1.0f,
						  0.5f, 0.5f, 1.0f, 0.0f,
						  0.5f,-0.5f, 1.0f, 1.0f };

		std::shared_ptr<VertexArray> va;
		va.reset(VertexArray::Create());
		va->Bind();


		std::shared_ptr<VertexBuffer> vb;
		vb.reset(VertexBuffer::Create(data, (int)16 * sizeof(float)));

		BufferLayout layout = {
			{ShaderDataType::Float2, "a_Position"},
			{ShaderDataType::Float2, "a_TexCoords"}
		};
		vb->SetLayout(layout);

		va->AddVertexBuffer(vb);

		va->UnBind();
		vb->UnBind();
		m_RawModel = new RawModel{ va };
	}

	void IconRenderer::RenderInspectorInfo()
	{

	}

	const unsigned int IconRenderer::Type() const
	{
		return m_ComponentID;
	}
	void IconRenderer::Render()
	{
		m_RawModel->va->Bind();
		m_Material->Bind();

		glm::mat4 viewMatrix = Renderer::GetViewMatrix();

		glm::mat4 modelMatrix(1.0f);
		modelMatrix = glm::translate(modelMatrix, m_Transform->Position);
		modelMatrix[0][0] = viewMatrix[0][0];
		modelMatrix[1][0] = viewMatrix[0][1];
		modelMatrix[2][0] = viewMatrix[0][2];
		modelMatrix[0][1] = viewMatrix[1][0];
		modelMatrix[1][1] = viewMatrix[1][1];
		modelMatrix[2][1] = viewMatrix[1][2];
		modelMatrix[0][2] = viewMatrix[2][0];
		modelMatrix[1][2] = viewMatrix[2][1];
		modelMatrix[2][2] = viewMatrix[2][2];
		modelMatrix = glm::scale(modelMatrix, m_Transform->Scale);
		glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;

		glm::mat4 projection = Renderer::GetProjectionMatrix();
		m_Material->m_Shader->SetUniform("u_projectionMatrix", projection);

		glm::mat4 viewTransform = Renderer::GetViewMatrix();

		m_Material->m_Shader->SetUniform("u_modelViewMatrix", modelViewMatrix);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
}

