#pragma once

#include "Engine/Materials/Phong.h"
#include "OpenGLMaterial.h"

namespace Engine {

	class OpenGLPhong : public Phong, public OpenGLMaterial
	{
	public:
		OpenGLPhong(OpenGLShader* shader, const std::string& name);

		virtual void Bind() override;

		// Inherited via GLMaterial
		virtual void RenderInspectorInfo() override;
	};

}
