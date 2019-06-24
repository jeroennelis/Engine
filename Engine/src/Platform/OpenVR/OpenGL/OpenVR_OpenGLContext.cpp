#include "enpch.h"
#include "OpenVR_OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Engine {

	OpenVR_OpenGLContext::OpenVR_OpenGLContext(GLFWwindow* windowHandle)
		:OpenGLContext(windowHandle)
	{
	}

	void OpenVR_OpenGLContext::Init()
	{
		OpenGLContext::Init();
	}

	void OpenVR_OpenGLContext::SwapBuffers()
	{
		OpenGLContext::SwapBuffers();
	}
}

