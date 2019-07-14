#pragma once

#include "GL.h"

namespace Engine {

	class OpenGLTexture
	{
	private: 
		unsigned int m_RendererID;
		std::string m_FilePath;
		unsigned char* m_LocalBuffer;
		int m_Width, m_Height, m_BPP;

	public:
		OpenGLTexture();
		OpenGLTexture(const std::string& path);
		~OpenGLTexture();

		void Bind(unsigned int slot = 0) const;
		void UnBind() const;

		void Update(unsigned char* buffer, int width, const int height);

		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }
	};
}
