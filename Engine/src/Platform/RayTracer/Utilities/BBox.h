#pragma once

#include "Ray.h"
#include "Constants.h"

namespace Engine {

	class BBox {

	public:
		double X0, X1, Y0, Y1, Z0, Z1;

		// default constructor
		BBox();
		
		// constructor
		BBox(const double& x0, const double& x1,
			const double& y0, const double& y1,
			const double& z0, const double& z1);

		// copy constructor
		BBox(const BBox& bBox);

		// assignment operator
		BBox& operator= (const BBox& rhs);

		// destructor
		~BBox();

		// Hit
		bool Hit(const Ray& ray) const;

		// Inside 
		bool Inside(const glm::vec3& p) const;
	};
}