#include "enpch.h"
#include "OpenGLIconMaterial.h"
#include "imgui.h"
#include "Platform/OpenGl/Loader.h"

namespace Engine {

	OpenGLIconMaterial::OpenGLIconMaterial(OpenGLShader* shader, const std::string& name)
		:OpenGLMaterial(shader, name), m_Texture(new GLTexture()), m_Colour(new glm::vec4(1.0f,1.0f,1.0f,1.0f))
	{
	}

	void OpenGLIconMaterial::RenderInspectorInfo()
	{
		static bool open = true;
		ImGui::SetNextTreeNodeOpen(open);
		if (ImGui::TreeNode("Material"))
		{
			renderTexureButton(&m_Texture);

			ImGui::TreePop();
			open = true;
		}
		else
		{
			open = false;
		}
	}

	void OpenGLIconMaterial::Bind()
	{
		m_Shader->Bind();
		m_Texture->Bind(0);
		m_Shader->SetUniform1i("textureSampler", 0);

		m_Shader->SetUniform("u_colour", *m_Colour);
	}

	void OpenGLIconMaterial::renderTexureButton(ImageTexture** imageTexture)
	{
		ImTextureID texID = (ImTextureID)(UINT_PTR)dynamic_cast<GLTexture*>(*imageTexture)->GetID();
		//ImTextureID texID = (ImTextureID)(UINT_PTR)21;

		ImGui::ColorEdit4("color", (float*)m_Colour);

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

