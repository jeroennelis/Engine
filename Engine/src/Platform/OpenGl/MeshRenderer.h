#pragma once
#include "Engine/Components/RenderCompont.h"
#include "RawModel.h"
#include "Engine/Components/Transform.h"
#include "Platform/OpenGl/Materials/OpenGLMaterial.h"

namespace Engine {

	class MeshRenderer : public RenderComponent
	{
	public:

		MeshRenderer(OpenGLMaterial* material, RawModel* rawModel, Transform* transform);
		~MeshRenderer();

		inline void SetMaterial(OpenGLMaterial* mat) { m_Material = mat; }
		inline OpenGLMaterial* GetMaterial() {return m_Material; }
		inline RawModel* GetRawModel() { return m_RawModel; }

		// Inherited via Component
		virtual void RenderInspectorInfo() override;
		virtual const unsigned int Type() const override;

		virtual void Render() override;

		void DrawOutline();

	private:	
		OpenGLMaterial*	m_Material;
		RawModel*	m_RawModel;
		Transform*	m_Transform;


	};
}