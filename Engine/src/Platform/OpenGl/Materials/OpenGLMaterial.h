#pragma once

#include "Platform/OpenGl/Renderer/OpenGLShader.h"
#include "Platform/OpenGl/FrameBuffer.h"

namespace Engine {

	class OpenGLMaterial
	{
	public:
		OpenGLMaterial(OpenGLShader* shader, const std::string& name);

		virtual void Bind() = 0;

		virtual void RenderInspectorInfo() = 0;
		const void RenderProjectInfo()const;

		void RenderPreview();

		OpenGLShader* m_Shader;

	protected:
		std::string m_Name;
		FrameBuffer* m_Preview;
	};
}
