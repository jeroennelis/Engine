#pragma once

#include "Engine/Components/Transform.h"
#include "Engine/Components/RenderCompont.h"
#include "Materials/OpenGLMaterial.h"
#include "RawModel.h"

namespace Engine
{
	class TerrainRenderer : public RenderComponent
	{
	public:
		TerrainRenderer(OpenGLMaterial* material, RawModel* rawModel, Transform* transform);
		~TerrainRenderer();

		virtual void Render() override;
		virtual void RenderInspectorInfo() override;

	private:
		OpenGLMaterial* m_Material;
		RawModel* m_RawModel;
		Transform* m_Transform;
	};
}
