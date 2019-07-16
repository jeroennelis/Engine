#pragma once

#include "Material.h"
#include "Engine/BRDF/Lambertian.h"

namespace Engine {

	class Matte : public Material
	{
	public:

		Matte();
		Matte(Lambertian* ambient, Lambertian* diffuse);

		~Matte();

		void SetKa(const float ka);

		void SetKd(const float kd);

		void SetCd(Texture* c);

	protected:
		Lambertian* m_AmbientBRDF;
		Lambertian* m_DiffuseBRDF;
	};
}
