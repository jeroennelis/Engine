#pragma once

#include "Engine/Renderer/Buffer.h"

namespace Engine {

	

	/*class OpenGLVertexArrayTemp : public VertexArrayTemp
	{
	public:
		OpenGLVertexArrayTemp();
		virtual ~OpenGLVertexArrayTemp();

		void Bind() const override;
		void UnBind() const override;

		void AddBuffer(VertexBuffer* vb, VertexBufferLayout* layout);

	private:
		unsigned int m_RendererID;
	};*/


	///////////////////////////////////////////////////
	// OpenGL VertexBuffer ////////////////////////////
	///////////////////////////////////////////////////

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(const void* data, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		virtual const BufferLayout& GetLayout() const override { return m_Layout; }

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};



	class OpenGLIndexBuffer : public IndexBuffer
	{
	public :
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();
		
		virtual void Bind() const override;
		virtual void UnBind() const override;

		inline uint32_t GetCount() const override { return m_Count; }

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}