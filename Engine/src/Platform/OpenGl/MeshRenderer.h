#pragma once
#include "Engine/Components/Component.h"
#include "RawModel.h"
#include "Platform/OpenGl/OpenGLMaterial.h"
#include "Engine/Components/Transform.h"

namespace Engine {

	class MeshRenderer : public Component
	{
	public:

		MeshRenderer(OpenGLMaterial* material, RawModel* rawModel, Transform* transform);
		~MeshRenderer();

		inline void SetMaterial(OpenGLMaterial* mat) { m_Material = mat; }
		inline RawModel* GetRawModel() { return m_RawModel; }

		// Inherited via Component
		virtual void Update() override;
		virtual void RenderInspectorInfo() override;
		virtual const unsigned int Type() const override;

		void Draw();

		const static unsigned int ComponentType;

	private:	
		OpenGLMaterial*	m_Material;
		RawModel*	m_RawModel;
		Transform*	m_Transform;

		glm::mat4 CreateProjectionMatrix();
	};
}