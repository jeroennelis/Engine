#include "enpch.h"
#include "OpenGLMaterial.h"
#include "imgui.h"
#include "Platform/OpenGl/Loader.h"

#include "Engine/Logic/Scene.h"
#include "Engine/Application.h"
#include "Platform/OpenGl/FrameBuffer.h"

namespace Engine {
	OpenGLMaterial::OpenGLMaterial(Shader* shader, const std::string& name)
		:m_Shader(shader),
		m_Name(name)
	{
		m_Preview = new FrameBuffer(512, 512);
	}

	void OpenGLMaterial::Bind()
	{
		m_Shader->Bind();
	}

	const void OpenGLMaterial::RenderProjectInfo() const
	{
		ImTextureID texID = (ImTextureID)(UINT_PTR)m_Preview->GetTexture();
		bool clicked = ImGui::ImageButton(texID, { 50, 50 }, { 0, 1 }, { 1,0 }); //TODO imgui pop

		if (ImGui::BeginDragDropSource())
		{
			ImGui::SetDragDropPayload("Material", "test", 5);
			Loader::Get()->SetDraggedMaterial(const_cast<OpenGLMaterial*>(this));
			EN_CORE_INFO("dragging");
			ImGui::EndDragDropSource();
		}
		else if (clicked)
		{
			Scene::SetSelectedMaterial(const_cast<OpenGLMaterial*>(this));
		}
	}

	void OpenGLMaterial::RenderPreview()
	{
		glViewport(0, 0, 512, 512);
		m_Preview->Bind();
		GLCall(glClearColor(0.0, 0.0, 0.0, 1));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_CULL_FACE);
		glEnable(GL_BACK);
		Loader::Get()->GetModel("sphere")->va->Bind();
		//Loader::Get()->GetModel("sphere")->ib->Bind();
		Bind();

		glm::mat4 projection = glm::mat4(1.0);
		m_Shader->SetUniform("u_projectionMatrix", projection);

		Camera* camera = Scene::Current()->GetGameCamera();
		glm::mat4 viewTransform = glm::mat4(1.0);

		m_Shader->SetUniform("u_viewMatrix", viewTransform);

		glm::mat4 transform = glm::mat4(1.0);
		m_Shader->SetUniform("u_transformationMatrix", transform);

		glDrawElements(GL_TRIANGLES, Loader::Get()->GetModel("sphere")->va->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		m_Preview->Unbind();
		glViewport(0, 0, Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());			//TODO set viewport while binding fb
	}
}