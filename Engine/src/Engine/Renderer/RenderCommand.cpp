#include "enpch.h"

#include "RenderCommand.h"
#include "Platform/OpenGl/Renderer/OpenGLRendererAPI.h"

namespace Engine {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}