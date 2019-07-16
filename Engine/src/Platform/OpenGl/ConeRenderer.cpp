#include "enpch.h"
#include "ConeRenderer.h"
#include "imgui.h" 
#include "Loader.h"
#include "Engine/Components/Camera.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Logic/Scene.h"
#include "Engine/Application.h"

namespace Engine{

	const unsigned int ConeRenderer::ComponentType = COMP_CONECLOUDRENDERER;

	ConeRenderer::ConeRenderer(OpenGLMaterial* material, const RawModel& rawModel, Transform* transform)
		:Component("conerenderer", ComponentType), m_Material(material),  m_RawModel(rawModel), m_Transform(transform)
	{
	}

	ConeRenderer::~ConeRenderer()
	{
		
	}

	void ConeRenderer::Update()
	{
	}

	void ConeRenderer::RenderInspectorInfo()
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

	const unsigned int ConeRenderer::Type() const
	{
		return m_ComponentID;
	}

	void ConeRenderer::Draw()
	{
		glDisable(GL_CULL_FACE);
		glEnable(GL_BACK);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		
		m_RawModel.va->Bind();
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

		(glDrawElements(GL_TRIANGLES, m_RawModel.va->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr));
		
		glDisable(GL_BLEND);
		
	}

}

