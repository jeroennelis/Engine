#pragma once

#include "OpenGLMaterial.h"

namespace Engine {

	class OpenGLCone : public OpenGLMaterial
	{

	public:
		OpenGLCone(OpenGLShader* shader, const std::string& name);
		// Inherited via GLMaterial
		virtual void RenderInspectorInfo() override;

		virtual void Bind() override;
	};
}