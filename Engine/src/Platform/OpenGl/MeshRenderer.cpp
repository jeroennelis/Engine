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
	const unsigned int MeshRenderer::ComponentType = COMP_MESHRENDERER;
	
	MeshRenderer::MeshRenderer(Material* material, RawModel* rawModel, Transform* transform)
		:Component("MeshRenderer", ComponentType), m_Material(material), m_RawModel(rawModel), m_Transform(transform)
	{
	}

	MeshRenderer::~MeshRenderer()
	{
	}

	void MeshRenderer::Update()
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

	void MeshRenderer::Draw()
	{
		glEnable(GL_CULL_FACE);
		glEnable(GL_BACK);
		m_RawModel->va->Bind();
		//m_RawModel->ib->Bind();
		m_Material->Bind();

		//glm::mat4 projection = CreateProjectionMatrix();
		glm::mat4 projection = Renderer::GetProjectionMatrix();
		m_Material->m_Shader->SetUniform("u_projectionMatrix", &projection);

		Camera* camera = Scene::Current()->GetGameCamera();
		glm::mat4 viewTransform = camera->GetViewMatrix();
		
		m_Material->m_Shader->SetUniform("u_viewMatrix", &viewTransform);
		
		m_Material->m_Shader->SetUniform("u_transformationMatrix", &m_Transform->TransformationMatrix);

		glDrawElements(GL_TRIANGLES, m_RawModel->va->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	glm::mat4 MeshRenderer::CreateProjectionMatrix()
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
}


