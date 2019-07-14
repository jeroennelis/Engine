#pragma once

#include "RTMaterial.h"
#include "..//BRDFs/RTLambertian.h"

namespace Engine {

	class RTMatte : public RTMaterial
	{
	public:

		RTMatte();
		~RTMatte();

		void SetKa(const float ka);

		void SetKd(const float kd);

		void SetCd(Texture* c);

		virtual glm::vec3 Shade(ShadeRec& sr)override;

		virtual glm::vec3 ShadeAreaLight(ShadeRec& sr) override;

	private:

		RTLambertian* m_AmbientBRDF;
		RTLambertian* m_DiffuseBRDF;
	};
}
