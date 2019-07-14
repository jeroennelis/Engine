#pragma once

#include "RTLight.h"
#include "..//GeometricObjects/GeometricObject.h"


namespace Engine {

	class RTAreaLight : public RTLight
	{
	public:
		RTAreaLight();

		~RTAreaLight();

		inline void SetObject(GeometricObject* object) { m_Object = object; m_Material = object->GetMaterial(); }

		virtual glm::vec3 GetDirection(ShadeRec& sr) override;

		virtual bool InShadow(const Ray& ray, const ShadeRec& sr) const override;

		virtual glm::vec3 L(ShadeRec& sr) override;

		virtual float G(const ShadeRec& sr) const override;

		virtual float Pdf(ShadeRec& sr) const override;

	private:
		
		GeometricObject* m_Object;
		RTMaterial* m_Material;
		glm::vec3 m_SamplePoint;
		glm::vec3 m_LightNormal;
		glm::vec3 m_Wi;
	};
}
