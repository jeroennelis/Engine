#pragma once

#include "RTMaterial.h"
#include "../BRDFs/Lambertian.h"
#include "../BRDFs/GlossySpecular.h"

namespace Engine {

	class RTPhong : public RTMaterial 
	{
	public : 
		RTPhong();
		~RTPhong();

		virtual glm::vec3 Shade(ShadeRec& sr);

		void SetKa(const float ka);

		void SetKd(const float kd);

		void SetKs(const float ks);

		void SetExp(const float exp);

		void SetCd(const glm::vec3& c);

	private:
		Lambertian* m_AmbientBRDF;
		Lambertian* m_DiffuseBRDF;
		GlossySpecular* m_SpecularBRDF;
	};
}