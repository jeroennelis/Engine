#include "enpch.h"

#include "GLTexture.h"
#include "stb_image.h"

namespace Engine {
	Engine::GLTexture::GLTexture()
	{
		GLCall(glGenTextures(1, &m_RendererID));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

		GLubyte data[] = { 255, 255, 255, 255 };

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));


		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	}

	Engine::GLTexture::GLTexture(const std::string& path)
		:m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
	{
		//stbi_set_flip_vertically_on_load(1);
		m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

		EN_CORE_INFO("{0}", path.c_str());



		GLCall(glGenTextures(1, &m_RendererID));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));

		//midmapping
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
		GLCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4));




		if (m_LocalBuffer)
		{
			stbi_image_free(m_LocalBuffer);
		}
	}

	Engine::GLTexture::~GLTexture()
	{
		GLCall(glDeleteTextures(1, &m_RendererID));
	}

	void Engine::GLTexture::Bind(unsigned int slot /* =0 */) const
	{
		//TODO: check nr of TEXTURE SLOTS
		GLCall(glActiveTexture(GL_TEXTURE0 + slot));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
	}

	void Engine::GLTexture::UnBind() const
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}

	void Engine::GLTexture::Update(unsigned char* buffer, int width, const int height)
	{
		Bind();
		m_LocalBuffer = buffer;
		m_Width = width;
		m_Height = height;
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
		UnBind();
	}
}


