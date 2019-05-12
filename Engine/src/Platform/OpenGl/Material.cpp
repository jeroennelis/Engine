#include "enpch.h"

#include "Material.h"
#include "imgui.h"
#include "Loader.h"

#include "Engine/Components/Camera.h"
#include "Engine/Logic/Scene.h"
#include "Engine/Application.h"


namespace Engine {

	Material::Material(Shader* shader, const std::string& name)
		:m_Shader(shader), m_Name(name)
	{
		InitProperties();
		m_Preview = new FrameBuffer(512, 512);
	}

	Material::~Material()
	{
		delete m_Preview;
		for (MaterialProperty* prop : m_Properties)
			delete prop;
	}

	void Material::AddProperty(MaterialProperty *prop)
	{
		m_Properties.push_back(prop);
	}
	
	void Material::Bind()
	{
		m_Shader->Bind();
		
		for (MaterialProperty* prop : m_Properties)
		{
			prop->SetProperty(m_Shader);
		}
	}

	void Material::RenderInspectorInfo()
	{
		if(ImGui::TreeNode("Material"))
		{
			for (MaterialProperty* prop : m_Properties)
			{
				prop->RenderInspectorInfo();
			}
			ImGui::TreePop();
			RenderPreview();
		}
	}

	const void Material::RenderProjectInfo()const
	{
		ImTextureID texID = (ImTextureID)(UINT_PTR)m_Preview->GetTexture();
		bool clicked = ImGui::ImageButton(texID, ImVec2(50, 50)); //TODO imgui pop
		
		if (ImGui::BeginDragDropSource())
		{
			ImGui::SetDragDropPayload("Material", "test", 5);
			Loader::Get()->SetDraggedMaterial(const_cast<Material*>(this));
			EN_CORE_INFO("dragging");
			ImGui::EndDragDropSource();
		}
		else if (clicked)
		{
			Scene::SetSelectedMaterial(const_cast<Material*>(this));
		}
		
	}

	void Material::RenderPreview()
	{
		glViewport(0, 0, 512, 512);
		m_Preview->Bind();
		GLCall(glClearColor(0.0, 0.0, 0.0, 1));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glEnable(GL_CULL_FACE);
		glEnable(GL_BACK);
		Loader::Get()->GetModel("sphere")->va->Bind();
		Loader::Get()->GetModel("sphere")->ib->Bind();
		Bind();

		glm::mat4 projection = glm::mat4(1.0);
		m_Shader->SetUniform("u_projectionMatrix", &projection);

		Camera* camera = Scene::Current()->GetGameCamera();
		glm::mat4 viewTransform = glm::mat4(1.0);

		m_Shader->SetUniform("u_viewMatrix", &viewTransform);

		glm::mat4 transform = glm::mat4(1.0);
		m_Shader->SetUniform("u_transformationMatrix", &transform);

		GLCall(glDrawElements(GL_TRIANGLES, Loader::Get()->GetModel("sphere")->ib->GetCount(), GL_UNSIGNED_INT, nullptr));
		m_Preview->Unbind();
		glViewport(0, 0, Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());			//TODO set viewport while binding fb
	}

	glm::mat4 Material::CreateProjectionMatrix()
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

	void Material::InitProperties()
	{
		for (const auto& prop : m_Shader->GetProperties())
		{
			if (prop.second == "float")
			{
				AddProperty(new FloatProperty(prop.first, 0.5f));
			}

			if (prop.second == "Color")
			{
				AddProperty(new ColorProperty(prop.first, glm::vec4(0.8f, 0.01f, 0.9f, 1.0f)));
			}
		}
	}
}