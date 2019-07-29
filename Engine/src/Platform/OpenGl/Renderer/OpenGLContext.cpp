#include "enpch.h"

#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Engine {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		EN_CORE_ASSERT(status, "Failed to initialize Glad!");

		EN_CORE_INFO("OpenGL info:");
		EN_CORE_INFO("\tVendor: \t{0}", glGetString(GL_VENDOR));
		EN_CORE_INFO("\tRenderer: \t{0}", glGetString(GL_RENDERER));
		EN_CORE_INFO("\tVersion: \t{0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}