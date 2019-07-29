#pragma once

#include "GL.h"
#include "Engine/Textures/ImageTexture.h"

namespace Engine {

	class GLTexture : public ImageTexture
	{
	private: 
		unsigned int m_RendererID;
		std::string m_FilePath;
		unsigned char* m_LocalBuffer;
		int m_Width, m_Height, m_BPP;

	public:
		GLTexture();
		GLTexture(const std::string& path);
		~GLTexture();

		void Bind(unsigned int slot = 0) const override;
		void UnBind() const;

		void Update(unsigned char* buffer, int width, const int height);

		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }

		inline unsigned int GetID() const { return m_RendererID; }
	};
}
