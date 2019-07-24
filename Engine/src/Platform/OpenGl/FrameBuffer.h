#pragma once
#include  "Engine/Core.h" 
#include  "glad/glad.h" 


namespace Engine {
	
	class FrameBuffer
	{
	public:
		FrameBuffer(int width, int height);
		~FrameBuffer();

		void Bind();
		void Unbind();
		GLuint GetTexture() { return m_TextureID; }

	private:
		void CreateFrameBuffer();
		void CreateTextureAttachment(int width, int height);
		void CreateRenderBuffer(int width, int height);
		void CreateStencilBuffer(int width, int height);


	private:
		GLuint m_RendererID;
		GLuint m_TextureID;
		GLuint m_RenderBufferID;
	};
}