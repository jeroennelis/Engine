#pragma once

#include  "Engine/Core.h" 
#include  "Engine/Events/Event.h" 
#include "Engine/Renderer/Renderer.h"

namespace Engine {

	enum RENDER_API {
		GL,
		VULKAN
	};

	struct WindowProperties
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProperties(const std::string& title =  "Engine" ,
			unsigned int width = 1280,
			unsigned int height = 720)
			:Title(title), Width(width), Height(height) {}
	};

	class ENGINE_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		virtual double GetFPS() = 0;
		virtual double GetFrameRate() = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(RendererAPI::API api, const WindowProperties& props = WindowProperties());
	};
}