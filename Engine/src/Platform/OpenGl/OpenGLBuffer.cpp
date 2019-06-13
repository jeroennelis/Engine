#include "enpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Engine {
	
	/////////////////////////////////////////////////////
	//// OpenGL Vertex Array ////////////////////////////
	/////////////////////////////////////////////////////
	//
	//OpenGLVertexArrayTemp::OpenGLVertexArrayTemp()
	//{
	//	(glGenVertexArrays(1, &m_RendererID));
	//}

	//OpenGLVertexArrayTemp::~OpenGLVertexArrayTemp()
	//{
	//	(glDeleteVertexArrays(1, &m_RendererID));
	//}
	//

	//void OpenGLVertexArrayTemp::Bind() const
	//{
	//	(glBindVertexArray(m_RendererID));
	//}

	//void OpenGLVertexArrayTemp::UnBind() const
	//{
	//	(glBindVertexArray(0));
	//}

	//void OpenGLVertexArrayTemp::AddBuffer(VertexBuffer* vb, VertexBufferLayout* layout)
	//{
	//	Bind();
	//	vb->Bind();
	//	const auto& elements = layout->GetElements();
	//	unsigned int offset = 0;
	//	for (unsigned int i = 0; i < elements.size(); i++)
	//	{
	//		const auto& element = elements[i];
	//		(glEnableVertexAttribArray(i));
	//		(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout->GetStride(), (const void*)(UINT_PTR)offset));
	//		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	//	}
	//}

	///////////////////////////////////////////////////
	// OpenGL VertexBuffer ////////////////////////////
	///////////////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(const void * data, uint32_t size)
	{
		(glGenBuffers(1, &m_RendererID));
		(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
		(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	///////////////////////////////////////////////////
	// OpenGL IndexBuffer /////////////////////////////
	///////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		:m_Count(count)
	{
		(glGenBuffers(1, &m_RendererID));
		(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
		(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW));
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}