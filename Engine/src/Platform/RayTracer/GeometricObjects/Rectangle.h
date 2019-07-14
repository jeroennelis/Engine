#pragma once

#include "GeometricObject.h"
#include "..//Samplers/Sampler.h"

namespace Engine {

	class Rectangle : public GeometricObject
	{
	public:
		Rectangle(const glm::vec3& p0, const glm::vec3& a, const glm::vec3& b, glm::vec3 normal);

		~Rectangle();

		inline void SetSampler(Sampler* sampler) { m_Sampler = sampler; }

		virtual glm::vec3 Sample() override;

		virtual float Pdf(ShadeRec& sr) override;

		virtual glm::vec3 GetNormal(const glm::vec3& p) override;

		// Inherited via GeometricObject
		virtual GeometricObject* clone(void) const override;

		virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const override;

	private:
		glm::vec3 m_P0;
		glm::vec3 m_A;
		glm::vec3 m_B;
		glm::vec3 m_Normal;
		Sampler* m_Sampler;
		float m_InvArea;



	};
}
