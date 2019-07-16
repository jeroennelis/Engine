#pragma once

#include "Engine/Components/Component.h"

#include "RawModel.h"
#include "Engine/Components/Transform.h"
#include "Platform/OpenGl/Materials/OpenGLMaterial.h"

namespace Engine {

	class ConeRenderer : public Component
	{
	public:

		ConeRenderer(OpenGLMaterial* material, const RawModel& rawModel, Transform* transform);
		~ConeRenderer();

		inline void SetMaterial(OpenGLMaterial* mat) { m_Material = mat; }

		// Inherited via Component
		virtual void Update() override;
		virtual void RenderInspectorInfo() override;
		virtual const unsigned int Type() const override;

		void Draw();

		const static unsigned int ComponentType;

	private:
		OpenGLMaterial* m_Material;
		RawModel m_RawModel;
		Transform* m_Transform;

		glm::mat4 CreateProjectionMatrix();
	};
}