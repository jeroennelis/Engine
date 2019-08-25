#pragma once

#include "OpenGLMaterial.h"
#include "Engine/Materials/Material.h"
#include "Platform/OpenGl/GLTexture.h"


namespace Engine {

	class OpenGLSkyboxMaterial : public OpenGLMaterial, public Material
	{
	public:
		OpenGLSkyboxMaterial(OpenGLShader* shader, const std::string& name);

		// Inherited via OpenGLMaterial
		virtual void Bind() override;
		virtual void RenderInspectorInfo() override;

	private:
		std::vector<std::string> m_TextureFiles =
		{
			"../Engine/res/textures/skybox/right.png",
			"../Engine/res/textures/skybox/left.png",
			"../Engine/res/textures/skybox/top.png",
			"../Engine/res/textures/skybox/bottom.png",
			"../Engine/res/textures/skybox/back.png",
			"../Engine/res/textures/skybox/front.png"
		};

		GLuint m_TextureID;
	};
}