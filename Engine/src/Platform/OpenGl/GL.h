#pragma once
#include <glad/glad.h>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

inline void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

inline bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		EN_CORE_ERROR("[OpenGL Error] ({0}): {1} {2} : {3}", error, function, file, line);
		return false;
	}
	return true;
}

