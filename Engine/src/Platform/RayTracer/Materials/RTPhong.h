#pragma once

#include "RTMaterial.h"
#include "../BRDFs/RTLambertian.h"
#include "../BRDFs/RTGlossySpecular.h"

namespace Engine {

	class RTPhong : public RTMaterial 
	{
	public : 
		RTPhong();
		~RTPhong();

		virtual glm::vec3 Shade(ShadeRec& sr);

		virtual glm::vec3 ShadeAreaLight(ShadeRec& sr) override;

		void SetKa(const float ka);

		void SetKd(const float kd);

		void SetKs(const float ks);

		void SetExp(const float exp);

		void SetCd(Texture* c);

	private:
		RTLambertian* m_AmbientBRDF;
		RTLambertian* m_DiffuseBRDF;
		RTGlossySpecular* m_SpecularBRDF;
	};
}