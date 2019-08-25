#include "enpch.h"
#include "OpenGLPhong.h"
#include "imgui.h"
#include "Platform/OpenGl/BRDFs/OpenGLLambertian.h"
#include "Platform/OpenGl/BRDFs/OpenGLBRDF.h"
#include "Platform/OpenGl/BRDFs/OpenGLGlossySpecular.h"
#include "Platform/OpenGl/GLTexture.h"
#include "Platform/OpenGl/Loader.h"
#include "Engine/Logic/Scene.h"

namespace Engine {
	OpenGLPhong::OpenGLPhong(OpenGLShader* shader, const std::string& name)
		:OpenGLMaterial(shader, name),
		Phong(new OpenGLLambertian, new OpenGLLambertian, new OpenGLGlossySpecular, new GLTexture)
	{
	}

	void OpenGLPhong::Bind()
	{
		OpenGLMaterial::Bind();

		Texture_temp* tex = m_AmbientBRDF->GetCd();
		glm::vec4 vec = glm::vec4 (tex->GetColor(), 1.0 );
		m_Shader->SetUniform("u_Cd", vec);
		m_Shader->SetUniform("u_Ka", m_AmbientBRDF->GetKd());
		m_Shader->SetUniform("u_Kd", m_DiffuseBRDF->GetKd());
		m_Shader->SetUniform("u_Ks", m_SpecularBRDF->GetKs());
		m_Shader->SetUniform("u_epsilon", m_SpecularBRDF->GetExp());
		
		m_Texture->Bind(0);
		
		if(Scene::Current())
			m_Shader->SetLights("test", Scene::Current()->GetLights());

	}

	void OpenGLPhong::RenderInspectorInfo()
	{
		static bool open = true;
		ImGui::SetNextTreeNodeOpen(open);
		if (ImGui::TreeNode("Material"))
		{
			ImTextureID texID = (ImTextureID)(UINT_PTR)dynamic_cast<GLTexture*>(m_Texture)->GetID();
			//ImTextureID texID = (ImTextureID)(UINT_PTR)21;

			bool clicked = ImGui::ImageButton(texID, { 50, 50 }, { 0, 1 }, { 1,0 }); //TODO imgui pop
			if (ImGui::BeginDragDropTarget())
			{
				ImGuiDragDropFlags target_flags = 0;
				//target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;    // Don't wait until the delivery (release mouse button on a target) to do something
				//target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect; // Don't display the yellow rectangle
				if (const ImGuiPayload * payload = ImGui::AcceptDragDropPayload("texture", target_flags))
				{
					if (!ImGui::IsMouseDown(0))
					{
						m_Texture = Loader::Get()->DraggedTexture();
					}
				}
				ImGui::EndDragDropTarget();
			}
			

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
			open = true;
		}
		else
		{
			open = false;
		}
	}
}


