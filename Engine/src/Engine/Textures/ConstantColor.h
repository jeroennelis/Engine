#pragma once

#include "Texture.h"

namespace Engine {

	class ShadeRec;

	class ConstantColor : public Texture
	{
	public:

		inline void SetColor(const glm::vec3& color) { m_Color = color; }

	protected:
		glm::vec3 m_Color;
	};
}
