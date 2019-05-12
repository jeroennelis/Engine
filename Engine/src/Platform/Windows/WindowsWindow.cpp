#include  "enpch.h" 
#include  "WindowsWindow.h" 
		  
#include  "Engine/Events/ApplicationEvent.h" 
#include  "Engine/Events/MouseEvent.h" 
#include  "Engine/Events/KeyEvent.h" 

#include "Platform/OpenGl/OpenGLContext.h"
#include "Platform/Vulkan/VulkanContext.h"

//#include <glad/glad.h>

namespace Engine {

	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		EN_CORE_ERROR( "GLFW Error ({ 0 }) : {1}" , error, description);
	}

	Window* Window::Create(RENDER_API api,const WindowProperties& props)
	{
		return new WindowsWindow(api, props);
	}

	WindowsWindow::WindowsWindow(RENDER_API api, const WindowProperties& props)
	{

		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		EN_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);
		
		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			EN_CORE_ASSERT(success, Could not initialize GLFW!);
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		switch (api) {
			case GL:
				break;
			case VULKAN:
				glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
				break;
		}

		m_Window = glfwCreateWindow(props.Width, props.Height, "Vulkan", nullptr, nullptr);
		glfwSetWindowUserPointer(m_Window, &m_Data);

		switch (api) {
		case GL:
			m_Context = new OpenGLContext(m_Window);
			m_Context->Init();
			break;
		case VULKAN:
			m_Context = new VulkanContext(m_Window);
			m_Context->Init();
			break;
		}			

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow * window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow * window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow * window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow * window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

				KeyTypedEvent event(keycode);
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow * window, int button, int action, int mod)
			{
				WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow * window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow * window, double xPos, double yPos) {
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
			});
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	double WindowsWindow::GetFPS()
	{
		return 0;
	}

	double WindowsWindow::GetFrameRate()
	{
		return frameDelta;

	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
		double currentTIme = glfwGetTime();
		frameDelta = (currentTIme - previousTime);
		previousTime = currentTIme;
		//EN_CORE_INFO("{0} fps", 1/frameDelta);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		m_Data.VSync = enabled;
	}
	
	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

}