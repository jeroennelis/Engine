#pragma once

#include "OpenGLMaterial.h"
#include "Engine/Materials/Material.h"
#include "Platform/OpenGl/GLTexture.h"

namespace Engine {

	class OpenGLIconMaterial : public OpenGLMaterial, public Material
	{
	public:
		OpenGLIconMaterial(OpenGLShader* shader, const std::string& name);

		virtual void RenderInspectorInfo() override;

		virtual void Bind() override;

		void SetTexture(ImageTexture* texture) { m_Texture = texture; }
		void SetColor(glm::vec4* color) { m_Colour = color; }

	private:
		ImageTexture* m_Texture;
		glm::vec4* m_Colour;

	private:
		void renderTexureButton(ImageTexture** imageTexture);
	};

}