#pragma once

#include "Engine/BRDF/GlossySpecular.h"

namespace Engine {

	class OpenGLGlossySpecular : public GlossySpecular
	{
	public:


		// Inherited via GlossySpecular
		virtual void RenderInspectorInfo() override;

	};
}
