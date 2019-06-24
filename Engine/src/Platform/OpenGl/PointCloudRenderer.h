#pragma once

#include "Engine/Components/Component.h"

#include "RawModel.h"
#include "Platform/OpenGl/Material.h"
#include "Engine/Components/Transform.h"

namespace Engine {

	class PointCloudRenderer : public Component
	{
	public:

		PointCloudRenderer(Material* material, const std::vector<RawModel>& rawModel, Transform* transform);
		~PointCloudRenderer();

		inline void SetMaterial(Material* mat) { m_Material = mat; }

		// Inherited via Component
		virtual void Update() override;
		virtual void RenderInspectorInfo() override;
		virtual const unsigned int Type() const override;

		void Draw();

		const static unsigned int ComponentType;

	private:
		Material* m_Material;
		std::vector<RawModel> m_RawModels;
		Transform* m_Transform;

		glm::mat4 CreateProjectionMatrix();
	};
}