#include "enpch.h"
#include "TerrainRenderer.h"
#include "Materials/OpenGLMaterial.h"
#include "RawModel.h"
#include "Engine/Renderer/Renderer.h"

namespace Engine {

	TerrainRenderer::TerrainRenderer(OpenGLMaterial* material, RawModel* rawModel, Transform* transform)
		:RenderComponent("TerrainRenderer"), m_Material(material), m_RawModel(rawModel), m_Transform(transform)
	{

	}
	
	TerrainRenderer::~TerrainRenderer()
	{
	}


	void TerrainRenderer::Render()
	{
		glEnable(GL_CULL_FACE);
		glEnable(GL_BACK);
		m_RawModel->va->Bind();
		m_Material->Bind();

		glm::mat4 projection = Renderer::GetProjectionMatrix();
		m_Material->m_Shader->SetUniform("u_projectionMatrix", projection);

		glm::mat4 viewTransform = Renderer::GetViewMatrix();

		m_Material->m_Shader->SetUniform("u_viewMatrix", viewTransform);

		m_Material->m_Shader->SetUniform("u_transformationMatrix", m_Transform->TransformationMatrix);

		GLCall(glDrawElements(GL_TRIANGLES, m_RawModel->va->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr));
	}

	void TerrainRenderer::RenderInspectorInfo()
	{
		m_Material->RenderInspectorInfo();
	}
}


