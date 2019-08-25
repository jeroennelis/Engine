#pragma once

#include "Engine/Components/RenderCompont.h"
#include "Materials/OpenGLMaterial.h"
#include "RawModel.h"
#include "Engine/Components/Transform.h"

namespace Engine {

	class IconRenderer : public RenderComponent
	{
	public:
		IconRenderer(OpenGLMaterial* material, Transform* transform);

		inline void SetMaterial(OpenGLMaterial* mat) { m_Material = mat; }
		inline OpenGLMaterial* GetMaterial() { return m_Material; }
		inline RawModel* GetRawModel() { return m_RawModel; }

		// Inherited via Component
		virtual void RenderInspectorInfo() override;
		virtual const unsigned int Type() const override;

		virtual void Render() override;

	private:
		OpenGLMaterial* m_Material;
		RawModel* m_RawModel;
		Transform* m_Transform;
	};
}