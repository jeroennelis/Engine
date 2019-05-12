#pragma once
#include "Renderer.h"
#include "Engine/Components/Component.h"
#include "RawModel.h"
#include "Platform/OpenGl/Material.h"
#include "Engine/Components/Transform.h"

namespace Engine {

	class MeshRenderer : public Component
	{
	public:

		MeshRenderer(Material* material, RawModel* rawModel, Transform* transform);
		~MeshRenderer();

		inline void SetMaterial(Material* mat) { m_Material = mat; }

		// Inherited via Component
		virtual void Update() override;
		virtual void RenderInspectorInfo() override;
		virtual const unsigned int Type() const override;

		void Draw();

		const static unsigned int ComponentType;

	private:	
		Material*	m_Material;
		RawModel*	m_RawModel;
		Transform*	m_Transform;

		glm::mat4 CreateProjectionMatrix();
	};
}