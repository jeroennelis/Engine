#pragma once

#include "Engine/Textures/ConstantColor.h"
#include "RTTexture.h"

namespace Engine {

	class RTConstantColor : public ConstantColor, public RTTexture
	{
	public : 
		virtual glm::vec3 GetColor(const ShadeRec& sr) const override;
	};
}
