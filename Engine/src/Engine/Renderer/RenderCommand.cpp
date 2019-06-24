#include "enpch.h"

#include "RenderCommand.h"

#include "Platform/OpenGl/OpenGLRendererAPI.h"

namespace Engine {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}