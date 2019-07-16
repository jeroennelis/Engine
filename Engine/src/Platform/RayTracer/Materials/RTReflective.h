#pragma once

#include "RTPhong.h"

#include "..//BRDFs/RTPerfectSpecular.h"

namespace Engine {

	class RTReflective : public RTPhong
	{
	public:

		RTReflective();

		RTReflective(const RTReflective& rm);

		RTReflective& operator= (const RTReflective& rhs);

		virtual RTReflective* clone() const;

		~RTReflective();

		void SetKr(const float kr);

		void SetCr(Texture* cr);

		virtual glm::vec3 Shade(ShadeRec& sr) override;

	protected:

		RTPerfectSpecular* m_ReflectiveBRDF;
	};
}
