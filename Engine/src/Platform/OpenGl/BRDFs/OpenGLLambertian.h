#pragma once

#include "Engine/BRDF/Lambertian.h"
#include "OpenGLBRDF.h"

namespace Engine {

	class OpenGLLambertian : public Lambertian
	{
	public:
		virtual void Bind() override;

		// Inherited via OpenGLBRDF
		virtual void RenderInspectorInfo() override;
	};
}
