#pragma once

#include "Platform/OpenGl/OpenGLContext.h"

struct GLFWwindow;

namespace Engine {

	class OpenVR_OpenGLContext : public OpenGLContext
	{
	public:
		OpenVR_OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	protected:
		GLFWwindow* m_WindowHandle;
	};
}