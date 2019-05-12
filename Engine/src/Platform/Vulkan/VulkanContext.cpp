#include "enpch.h"
#include "VulkanContext.h"
#include <GLFW/glfw3.h>

Engine::VulkanContext::VulkanContext(GLFWwindow* windowHandle)
	:m_WindowHandle(windowHandle)
{
}

void Engine::VulkanContext::Init()
{
}

void Engine::VulkanContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}
