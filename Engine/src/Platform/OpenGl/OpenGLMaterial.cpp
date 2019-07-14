#include "enpch.h"

#include "OpenGLMaterial.h"
#include "imgui.h"
#include "Loader.h"

#include "Engine/Components/Camera.h"
#include "Engine/Logic/Scene.h"
#include "Engine/Application.h"


namespace Engine {

	OpenGLMaterial::OpenGLMaterial(Shader* shader, const std::string& name)
		:m_Shader(shader), m_Name(name)
	{
		InitProperties();
		m_Preview = new FrameBuffer(512, 512);
	}

	OpenGLMaterial::~OpenGLMaterial()
	{
		delete m_Preview;
		for (MaterialProperty* prop : m_Properties)
			delete prop;
	}

	void OpenGLMaterial::AddProperty(MaterialProperty *prop)
	{
		m_Properties.push_back(prop);
	}
	
	void OpenGLMaterial::Bind()
	{
		m_Shader->Bind();
		
		for (MaterialProperty* prop : m_Properties)
		{
			prop->SetProperty(m_Shader);
		}
	}

	void OpenGLMaterial::RenderInspectorInfo()
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

	const void OpenGLMaterial::RenderProjectInfo()const
	{
		ImTextureID texID = (ImTextureID)(UINT_PTR)m_Preview->GetTexture();
		bool clicked = ImGui::ImageButton(texID, ImVec2(50, 50)); //TODO imgui pop
		
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
		m_Shader->SetUniform("u_projectionMatrix", &projection);

		Camera* camera = Scene::Current()->GetGameCamera();
		glm::mat4 viewTransform = glm::mat4(1.0);

		m_Shader->SetUniform("u_viewMatrix", &viewTransform);

		glm::mat4 transform = glm::mat4(1.0);
		m_Shader->SetUniform("u_transformationMatrix", &transform);

		glDrawElements(GL_TRIANGLES, Loader::Get()->GetModel("sphere")->va->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		m_Preview->Unbind();
		glViewport(0, 0, Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());			//TODO set viewport while binding fb
	}

	void OpenGLMaterial::InitProperties()
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
