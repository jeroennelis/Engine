#pragma once

#include "OpenGLMaterial.h"
#include "Engine/Textures/ImageTexture.h"

namespace Engine {

	class OpenGLTerrainMaterial : public OpenGLMaterial
	{
	public: 
		OpenGLTerrainMaterial(OpenGLShader* shader, const std::string& name);

		virtual void RenderInspectorInfo() override;

		virtual void Bind() override;

		inline void SetTextures(ImageTexture* backgroundTexture, ImageTexture* rTexture, ImageTexture* gTexture, ImageTexture* bTexture, ImageTexture* blendMap )
		{
			m_BackgroundTexture = backgroundTexture;
			m_RTexture = rTexture;
			m_GTexture = gTexture;
			m_BTexture = bTexture;
			m_BlendMap = blendMap;
		}

	private:
		ImageTexture* m_BackgroundTexture;
		ImageTexture* m_RTexture;
		ImageTexture* m_GTexture;
		ImageTexture* m_BTexture;
		ImageTexture* m_BlendMap;

	private:
		void renderTexureButton(ImageTexture** imageTexture);
	};
}
