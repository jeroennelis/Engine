#pragma once

#include "Platform/OpenGl/Shader.h"
#include "Platform/OpenGl/FrameBuffer.h"

namespace Engine {

	class OpenGLMaterial
	{
	public:
		OpenGLMaterial(Shader* shader, const std::string& name);

		virtual void Bind();

		virtual void RenderInspectorInfo() = 0;
		const void RenderProjectInfo()const;

		void RenderPreview();

		Shader* m_Shader;

	protected:
		std::string m_Name;
		FrameBuffer* m_Preview;
	};
}
