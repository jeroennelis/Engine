#pragma once

#include "Texture_temp.h"

namespace Engine {

	class ShadeRec;

	class ConstantColor : public Texture_temp
	{
	public:

		inline void SetColor(const glm::vec3& color) { m_Color = color; }
		virtual void RenderInspectorInfo();

	protected:
		glm::vec3 m_Color;

		// Inherited via Texture
		virtual glm::vec3 GetColor(const ShadeRec& sr) const override;
	};
}
