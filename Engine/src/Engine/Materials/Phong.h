#pragma once

#include "Material.h"
#include "Engine/Textures/Texture.h"
#include "Engine/BRDF/Lambertian.h"
#include "Engine/BRDF/GlossySpecular.h"

namespace Engine
{
	class Phong : public Material
	{

	public:
		Phong(Lambertian* ambient, Lambertian* diffuse, GlossySpecular* glossySpecular);

		void SetKa(const float ka);

		void SetKd(const float kd);

		void SetKs(const float ks);

		void SetExp(const float exp);

		void SetCd(Texture* c);

		virtual float GetKa();

		virtual float GetKd();

		virtual float GetKs();

		virtual float GetExp();

		virtual Texture* GetCd();

	protected:
		Lambertian* m_AmbientBRDF;
		Lambertian* m_DiffuseBRDF;
		GlossySpecular* m_SpecularBRDF;
	};
	


}
