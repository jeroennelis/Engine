#pragma once

#include "RTMaterial.h"
#include "..//BRDFs/Lambertian.h"

namespace Engine {

	class RTMatte : public RTMaterial
	{
	public:

		RTMatte();
		~RTMatte();

		void SetKa(const float ka);

		void SetKd(const float kd);

		void SetCd(const glm::vec3& c);

		virtual glm::vec3 Shade(ShadeRec& sr)override;

	private:

		Lambertian* m_AmbientBRDF;
		Lambertian* m_DiffuseBRDF;
	};
}
