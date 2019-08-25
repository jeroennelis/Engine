#include "enpch.h"
#include "OpenGLTerrainMaterial.h"
#include "..//GLTexture.h"
#include "imgui.h"
#include "Platform/OpenGl/Loader.h"

namespace Engine {

	OpenGLTerrainMaterial::OpenGLTerrainMaterial(OpenGLShader* shader, const std::string& name)
		:OpenGLMaterial(shader, name), m_BackgroundTexture(new GLTexture())
	{
	}

	void OpenGLTerrainMaterial::RenderInspectorInfo()
	{
		static bool open = true;
		ImGui::SetNextTreeNodeOpen(open);
		if (ImGui::TreeNode("Material"))
		{
			renderTexureButton(&m_BackgroundTexture);
			renderTexureButton(&m_RTexture);
			renderTexureButton(&m_GTexture);
			renderTexureButton(&m_BTexture);
			renderTexureButton(&m_BlendMap);

			ImGui::TreePop();
			open = true;
		}
		else
		{
			open = false;
		}
	}

	void OpenGLTerrainMaterial::Bind()
	{
		m_Shader->Bind();
		m_BackgroundTexture->Bind(0);
		m_Shader->SetUniform1i("backgroundTexture", 0);
		m_RTexture->Bind(1);
		m_Shader->SetUniform1i("RTexture", 1);
		m_GTexture->Bind(2);
		m_Shader->SetUniform1i("GTexture", 2);
		m_BTexture->Bind(3);
		m_Shader->SetUniform1i("BTexture", 3);
		m_BlendMap->Bind(4);
		m_Shader->SetUniform1i("BlendMap", 4);
		
	}

	void OpenGLTerrainMaterial::renderTexureButton(ImageTexture** imageTexture)
	{
		ImTextureID texID = (ImTextureID)(UINT_PTR)dynamic_cast<GLTexture*>(*imageTexture)->GetID();
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
					*imageTexture = Loader::Get()->DraggedTexture();
				}
			}
			ImGui::EndDragDropTarget();
		}

		RenderPreview();
	}
}


