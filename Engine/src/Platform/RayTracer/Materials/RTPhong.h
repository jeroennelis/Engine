#pragma once

#include "Engine/Materials/Phong.h"
#include "../BRDFs/RTLambertian.h"
#include "../BRDFs/RTGlossySpecular.h"

namespace Engine {

	class RTPhong : public Phong 
	{
	public : 
		RTPhong();
		~RTPhong();

		virtual glm::vec3 Shade(ShadeRec& sr);

		virtual glm::vec3 ShadeAreaLight(ShadeRec& sr) override;
	};
}