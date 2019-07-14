#pragma once

#include "..//GeometricObject.h"
#include "Engine/Maths.h"

namespace Engine {

	class Triangle : public GeometricObject
	{
	public:
		glm::vec3 V0, V1, V2;
		glm::vec3 Normal;

	public:
		// Default Constructor
		Triangle();

		// Constructor
		Triangle(const glm::vec3& v0, glm::vec3& v1, glm::vec3& v2);

		// Clone
		virtual Triangle* clone(void) const override;

		// Copy Constructor
		Triangle(const Triangle& triangle);

		// assignment operator 
		Triangle& operator= (const Triangle& rhs);

		// Get Bounding Box
		virtual BBox GetBoundingBox() override;

		//Compute Normal
		void ComputeNormal();

		// Hit
		virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const override;

		bool ShadowHit(const Ray& ray, float& tmin) const override;
	};

}
