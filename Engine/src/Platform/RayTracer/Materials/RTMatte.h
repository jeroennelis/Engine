#pragma once

#include "Engine/Materials/Matte.h"
#include "..//BRDFs/RTLambertian.h"

namespace Engine {

	class RTMatte : public Matte
	{
	public:

		RTMatte();
		~RTMatte();

		virtual glm::vec3 Shade(ShadeRec& sr) override;

		virtual glm::vec3 ShadeAreaLight(ShadeRec& sr) override;
	};
}
