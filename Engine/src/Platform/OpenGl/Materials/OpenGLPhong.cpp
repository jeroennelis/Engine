#include "enpch.h"
#include "OpenGLPhong.h"
#include "imgui.h"
#include "Platform/OpenGl/BRDFs/OpenGLLambertian.h"
#include "Platform/OpenGl/BRDFs/OpenGLBRDF.h"
#include "Platform/OpenGl/BRDFs/OpenGLGlossySpecular.h"

namespace Engine {
	OpenGLPhong::OpenGLPhong(Shader* shader, const std::string& name)
		:OpenGLMaterial(shader, name),
		Phong(new OpenGLLambertian, new OpenGLLambertian, new OpenGLGlossySpecular)
	{
	}

	void OpenGLPhong::Bind()
	{
		OpenGLMaterial::Bind();
		glm::vec4 vec = { m_AmbientBRDF->GetCd()->GetColor(),1.0 };
	
		m_Shader->SetUniform("u_Cd", vec);
		m_Shader->SetUniform("u_Ka", m_AmbientBRDF->GetKd());
		m_Shader->SetUniform("u_Kd", m_DiffuseBRDF->GetKd());
		m_Shader->SetUniform("u_Ks", m_SpecularBRDF->GetKs());
		m_Shader->SetUniform("u_epsilon", m_SpecularBRDF->GetKs());
	}

	void OpenGLPhong::RenderInspectorInfo()
	{
		if (ImGui::TreeNode("Material"))
		{
			ImGui::Text("Ambient");
			ImGui::PushID(1);
			m_AmbientBRDF->RenderInspectorInfo();
			ImGui::PopID();
			
			ImGui::Text("Diffuse");
			ImGui::PushID(2);
			m_DiffuseBRDF->RenderInspectorInfo();
			ImGui::PopID();
			
			ImGui::Text("Glossy Specular");
			ImGui::PushID(3);
			m_SpecularBRDF->RenderInspectorInfo();
			ImGui::TreePop();
			ImGui::PopID();
			RenderPreview();
		}
	}
}


