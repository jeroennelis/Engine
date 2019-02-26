#include "enpch.h"
#include "Renderer.h"
#include "Shader.h"


void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);

}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		EN_CORE_ERROR("[OpenGL Error] ({0}): {1} {2} : {3}", error, function, file, line);
		return false;
	}
	return true;
}

namespace Engine {
	void Renderer::Draw(const VertexArray & va, const IndexBuffer & ib, const Shader & shader) const
	{
		shader.Bind();
		va.Bind();
		ib.Bind();
		GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
	}

	void Renderer::Clear() const
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}
}