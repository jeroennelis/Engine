#include "enpch.h"

#include "MeshRenderer.h"
#include "imgui.h" 
#include <glm/gtx/transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtx\quaternion.hpp>
#include "Engine/Application.h"
#include "Engine/Components/Camera.h"
#include "Engine/Logic/Scene.h"
#include "Platform/OpenGl/Loader.h"

namespace Engine {
	
	MeshRenderer::MeshRenderer(OpenGLMaterial* material, RawModel* rawModel, Transform* transform)
		:RenderComponent("MeshRenderer"), m_Material(material), m_RawModel(rawModel), m_Transform(transform)
	{
	}

	MeshRenderer::~MeshRenderer()
	{
	}
	
	void MeshRenderer::RenderInspectorInfo()
	{
		bool open = ImGui::TreeNode(m_Name.c_str());
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* pl = ImGui::AcceptDragDropPayload("Material"))
			{
				m_Material = Loader::Get()->DraggedMaterial();
				Loader::Get()->SetDraggedMaterial(nullptr);
			}
			ImGui::EndDragDropTarget();
		}

		if (open)
		{
			m_Material->RenderInspectorInfo();
			ImGui::TreePop();
		}
		ImGui::Separator();
	}

	const unsigned int MeshRenderer::Type() const
	{
		return m_ComponentID;
	}

	void MeshRenderer::DrawOutline()
	{
		glEnable(GL_CULL_FACE);
		glEnable(GL_BACK);
		m_RawModel->va->Bind();
		//m_RawModel->ib->Bind();
		Shader* shader = Loader::Get()->GetShader("outline");
		shader->Bind();

		//glm::mat4 projection = CreateProjectionMatrix();
		glm::mat4 projection = Scene::Current()->GetSceneCamera()->GetProjectionMatrix();
		shader->SetUniform("u_projectionMatrix", projection);

		Camera* camera = Scene::Current()->GetGameCamera();
		glm::mat4 viewTransform = camera->GetViewMatrix();
		
		shader->SetUniform("u_viewMatrix", viewTransform);
		

		shader->SetUniform("u_transformationMatrix", m_Transform->TransformationMatrix * glm::scale(glm::vec3(1.1f,1.1f,1.1f)));

		GLCall(glDrawElements(GL_TRIANGLES, m_RawModel->va->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr));
	}

	void MeshRenderer::Render()
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
}


