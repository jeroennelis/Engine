#include  "enpch.h" 
#include  "FrameBuffer.h" 

namespace Engine {
	FrameBuffer::FrameBuffer(int width, int height)
	{
		CreateFrameBuffer();
		CreateTextureAttachment(width, height);
		CreateRenderBuffer(width, height);
	}


	FrameBuffer::~FrameBuffer()
	{
		(glDeleteFramebuffers(1, &m_RendererID));
		(glDeleteTextures(1, &m_TextureID));
	}

	void FrameBuffer::Bind()
	{
		(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
		//glViewport(0, 0, Window::Width,Window::Height);
	}

	void FrameBuffer::Unbind()
	{
		(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		//glViewport(0, 0, Window::Width, Window::Height);
	}

	void FrameBuffer::CreateFrameBuffer()
	{

		(glGenFramebuffers(1, &m_RendererID));
		(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
	}

	void FrameBuffer::CreateTextureAttachment(int width, int height)
	{
		(glGenTextures(1, &m_TextureID));
		(glBindTexture(GL_TEXTURE_2D, m_TextureID));
		(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));
		(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureID, 0));
	}

	void FrameBuffer::CreateRenderBuffer(int width, int height)
	{
		glGenRenderbuffers(1, &m_RenderBufferID);
		glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBufferID);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBufferID);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			EN_CORE_ERROR("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}


}
