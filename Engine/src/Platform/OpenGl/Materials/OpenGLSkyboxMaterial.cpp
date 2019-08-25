#include "enpch.h"
#include "OpenGLSkyboxMaterial.h"
#include <stb_image.h>

namespace Engine {


	OpenGLSkyboxMaterial::OpenGLSkyboxMaterial(OpenGLShader* shader, const std::string& name)
		:OpenGLMaterial(shader, name)
	{
		glGenTextures(1, &m_TextureID);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID);
		for (int i = 0; i < m_TextureFiles.size(); i++)
		{
			stbi_set_flip_vertically_on_load(0);
			int width;
			int height;
			int BPP;
			unsigned char* buffer = stbi_load(m_TextureFiles[i].c_str(), &width, &height, &BPP, 4);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
			GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			GLCall(glBindTexture(GL_TEXTURE_2D, 0));
			if (buffer)
				stbi_image_free(buffer);
			//TODO clean up 
		}
	}

	void OpenGLSkyboxMaterial::Bind()
	{
		m_Shader->Bind();
	}
	
	void OpenGLSkyboxMaterial::RenderInspectorInfo()
	{
	}
}
