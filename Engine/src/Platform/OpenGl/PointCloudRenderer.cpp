#include "enpch.h"
#include "PointCloudRenderer.h"
#include "imgui.h" 
#include "Loader.h"
#include "Engine/Components/Camera.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Logic/Scene.h"
#include "Engine/Application.h"

namespace Engine{

	const unsigned int PointCloudRenderer::ComponentType = COMP_POINTCLOUDRENDERER;

	PointCloudRenderer::PointCloudRenderer(OpenGLMaterial* material, const std::vector<RawModel>& rawModel, Transform* transform)
		:Component("PointCloudRenderer", ComponentType), m_Material(material),  m_RawModels(rawModel), m_Transform(transform)
	{
	}

	PointCloudRenderer::~PointCloudRenderer()
	{
		
	}

	void PointCloudRenderer::Update()
	{
	}

	void PointCloudRenderer::RenderInspectorInfo()
	{
		bool open = ImGui::TreeNode(m_Name.c_str());
		/*if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload * pl = ImGui::AcceptDragDropPayload("Material"))
			{
				m_Material = Loader::Get()->DraggedMaterial();
				Loader::Get()->SetDraggedMaterial(nullptr);
			}
			ImGui::EndDragDropTarget();
		}*/

		if (open)
		{
			//m_Material->RenderInspectorInfo();
			ImGui::TreePop();
		}
		ImGui::Separator();
	}

	const unsigned int PointCloudRenderer::Type() const
	{
		return m_ComponentID;
	}

	void PointCloudRenderer::Draw()
	{
		glEnable(GL_CULL_FACE);
		glEnable(GL_BACK);
		for (int i = 0; i < m_RawModels.size(); i++)
		{
			m_RawModels.at(i).va->Bind();
			//m_RawModel->ib->Bind();
			m_Material->Bind();

			//glm::mat4 projection = CreateProjectionMatrix();
			glm::mat4 projection = Renderer::GetProjectionMatrix();
			m_Material->m_Shader->SetUniform("u_projectionMatrix", projection);

			Camera* camera = Scene::Current()->GetGameCamera();
			glm::mat4 viewTransform = camera->GetViewMatrix();
			if (RendererAPI::GetAPI() == RendererAPI::API::OpenVR_OpenGL)
			{
				viewTransform = glm::mat4(1.0f);
			}

			m_Material->m_Shader->SetUniform("u_viewMatrix", viewTransform);

			m_Material->m_Shader->SetUniform("u_transformationMatrix", m_Transform->TransformationMatrix);

			glDrawArrays(GL_POINTS, 0, m_RawModels.at(i).va->GetCount());
		}
		
		
	}

}

