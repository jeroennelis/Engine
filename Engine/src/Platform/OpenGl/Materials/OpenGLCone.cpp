#include "enpch.h"
#include "OpenGLCone.h"

Engine::OpenGLCone::OpenGLCone(Shader* shader, const std::string& name)
	:OpenGLMaterial(shader, name)
{
}

void Engine::OpenGLCone::RenderInspectorInfo()
{
}

void Engine::OpenGLCone::Bind()
{
	m_Shader->Bind();
}
