#pragma once

namespace Engine {

	enum class RendererAPItest
	{
		None = 0, OpenGL = 1, Vulkan = 2
	};

	

	class Renderer
	{
	public:
		inline static RendererAPItest GetAPI() { return s_RendererAPI; }

		static void Create(RendererAPItest api);
		inline static Renderer* Get() { return s_Renderer; }
		virtual void Init() = 0;

		virtual void Render() = 0;
		virtual void CleanUp() = 0;

		virtual void* GetSceneFrameBufferTexture() = 0;
		virtual void* GetGameFrameBufferTexture() = 0;

	private:
		static RendererAPItest s_RendererAPI;
		static Renderer* s_Renderer;

	};
}