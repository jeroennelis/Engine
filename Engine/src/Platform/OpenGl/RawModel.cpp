#include "enpch.h"
#include "RawModel.h"
#include "Loader.h"
#include "Engine/Application.h"
#include "imgui.h"
#include "Engine/Renderer/OrthographicCamera.h"

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
	((OpenGLShader*)(Loader::Get()->GetShader("preview")))->SetUniform("u_projectionMatrix", projection);

	//Camera* camera = Scene::Current()->GetGameCamera();
	
	OrthographicCamera camera = OrthographicCamera(bBox.X0, bBox.X1, bBox.Y0, bBox.Y1,  bBox.Z0, bBox.Z1);

	float dx = bBox.X1 - bBox.X0;
	float dz = bBox.Z1 - bBox.Z0;
	float dy = (bBox.Y1 - bBox.Y0)/2 + bBox.Y0;


	float dnear = dx / (tan(glm::radians(90.0f / 2.0f)));

	float aspectRatio = 1;
	//fov
	float y_scale = (float)((1.0f / glm::tan(glm::radians(90.0f / 2.0f))) * aspectRatio);
	float x_scale = y_scale / aspectRatio;
	float frustum_length = 1000 - dnear;

	glm::mat4 projectionMatrix = glm::mat4();
	projectionMatrix[0][0] = x_scale;
	projectionMatrix[1][1] = y_scale;
	projectionMatrix[2][2] = -((1000 + dnear) / frustum_length);
	projectionMatrix[2][3] = -1;
	projectionMatrix[3][2] = -((2 * dnear * 1000) / frustum_length);
	projectionMatrix[3][3] = 0;






	glm::mat4 viewTransform = glm::mat4(1.0);

	((OpenGLShader*)(Loader::Get()->GetShader("preview")))->SetUniform("u_viewMatrix", viewTransform);
	((OpenGLShader*)(Loader::Get()->GetShader("preview")))->SetUniform("u_projectionMatrix", projectionMatrix);

	glm::mat4 transform = glm::mat4(1.0);
	transform = glm::translate(transform, glm::vec3(0, -dy, -(dnear + dz/2)));
	((OpenGLShader*)(Loader::Get()->GetShader("preview")))->SetUniform("u_transformationMatrix", transform);

	glDrawElements(GL_TRIANGLES, va->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	m_Preview->Unbind();
	glViewport(0, 0, Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());			//TODO set viewport while binding fb
}

void Engine::RawModel::RenderProjectInfo()
{
	if (m_Preview == nullptr)
		return;
	ImTextureID texID = (ImTextureID)(UINT_PTR)m_Preview->GetTexture();
	bool clicked = ImGui::ImageButton(texID, ImVec2(50, 50),ImVec2(0,1), ImVec2(1,0)); //TODO imgui pop

	if (ImGui::BeginDragDropSource())
	{
		ImGui::SetDragDropPayload("Model", "test", 5);
		Loader::Get()->SetDraggedRawModel(const_cast<RawModel*>(this));
		ImGui::EndDragDropSource();
	}
}
