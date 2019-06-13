#include "enpch.h"
#include "RawModel.h"
#include "Loader.h"
#include "Engine/Application.h"
#include "imgui.h"

Engine::RawModel::RawModel()
	:va(nullptr), m_Preview(nullptr)
{	
}

Engine::RawModel::RawModel(const std::shared_ptr<VertexArray>& vertexArray)
	:va(vertexArray)
{
	m_Preview = new FrameBuffer(512, 512);
}

void Engine::RawModel::RenderPreview()
{
	glViewport(0, 0, 512, 512);
	m_Preview->Bind();
	GLCall(glClearColor(0.0, 0.0, 0.0, 1));
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BACK);
	va->Bind();
	/*ib->Bind();*/
	Loader::Get()->GetShader("preview")->Bind();

	glm::mat4 projection = glm::mat4(1.0);
	Loader::Get()->GetShader("preview")->SetUniform("u_projectionMatrix", &projection);

	Camera* camera = Scene::Current()->GetGameCamera();
	glm::mat4 viewTransform = glm::mat4(1.0);

	Loader::Get()->GetShader("preview")->SetUniform("u_viewMatrix", &viewTransform);

	glm::mat4 transform = glm::mat4(1.0);
	//transform = glm::translate(transform, glm::vec3(0, 0, 10));
	Loader::Get()->GetShader("preview")->SetUniform("u_transformationMatrix", &transform);

	glDrawElements(GL_TRIANGLES, va->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	m_Preview->Unbind();
	glViewport(0, 0, Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());			//TODO set viewport while binding fb
}

void Engine::RawModel::RenderProjectInfo()
{
	ImTextureID texID = (ImTextureID)(UINT_PTR)m_Preview->GetTexture();
	bool clicked = ImGui::ImageButton(texID, ImVec2(50, 50)); //TODO imgui pop

	if (ImGui::BeginDragDropSource())
	{
		ImGui::SetDragDropPayload("Model", "test", 5);
		Loader::Get()->SetDraggedRawModel(const_cast<RawModel*>(this));
		EN_CORE_INFO("dragging");
		ImGui::EndDragDropSource();
	}
}
