#include "enpch.h"
#include "SkyboxRenderer.h"
#include "Engine/Renderer/Buffer.h"
#include "Engine/Renderer/VertexArray.h"
#include "Engine/Renderer/Renderer.h"


namespace Engine {
	SkyboxRenderer::SkyboxRenderer(OpenGLMaterial* material)
		:RenderComponent("SkyboxRenderer"), m_Material(material)
	{
		std::shared_ptr<VertexArray> va;
		va.reset(VertexArray::Create());
		va->Bind();


		std::shared_ptr<VertexBuffer> vb;
		vb.reset(VertexBuffer::Create(m_Vertices.data(), (int)m_Vertices.size() * sizeof(float)));

		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"}
		};
		vb->SetLayout(layout);

		va->AddVertexBuffer(vb);
		va->SetCount(m_Vertices.size() / 3);



		va->UnBind();
		vb->UnBind();
		m_RawModel = va;
	}

	SkyboxRenderer::~SkyboxRenderer()
	{
	}
	void SkyboxRenderer::Render()
	{
		m_RawModel.va->Bind();
		m_Material->Bind();

		glm::mat4 projection = Renderer::GetProjectionMatrix();
		m_Material->m_Shader->SetUniform("u_projectionMatrix", projection);

		glm::mat4 viewTransform = Renderer::GetViewMatrix();

		viewTransform[3][0] = 0;
		viewTransform[3][1] = 0;
		viewTransform[3][2] = 0;

		m_Material->m_Shader->SetUniform("u_viewMatrix", viewTransform);

		(glDrawArrays(GL_TRIANGLES, 0, m_RawModel.va->GetCount()));
	}
}

