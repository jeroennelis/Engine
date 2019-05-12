#pragma once

#include "enpch.h"

#include "Engine/Core.h"

namespace Engine {

	class RenderAPI
	{
	public:

		virtual ~RenderAPI() {};

		virtual void Init() = 0;
		virtual void Render() = 0;
		virtual void CleanUp() = 0;

		virtual void* GetSceneFrameBufferTexture() = 0;
		virtual void* GetGameFrameBufferTexture() = 0;
	};
}
