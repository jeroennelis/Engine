#pragma once

#include  "Engine/window.h" 

#include <GLFW/glfw3.h>
#include "Engine/Renderer/GraphicsContext.h"
#include "Platform/OpenGl/Renderer/OpenGLContext.h"

namespace Engine {

	

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(RendererAPI::API api, const WindowProperties& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		virtual double GetFPS() override;
		virtual double GetFrameRate() override;


		virtual inline void* GetNativeWindow() const override { return m_Window; }
	private:
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;
		GraphicsContext * m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;

		double previousTime;
		double frameDelta;

	};
}
