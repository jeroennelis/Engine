#pragma once

#include "GeometricObject.h"

namespace Engine {

	//-------------------------------------------------------------------- class Plane

	class Plane : public GeometricObject {

	public:

		Plane(void);   												// default constructor

		Plane(const glm::vec3& p, const glm::vec3& n);			// constructor	

		Plane(const Plane& p); 									// copy constructor

		virtual Plane* 												// virtual copy constructor
			clone(void) const;

		Plane& 														// assignment operator
			operator= (const Plane& rhs);

		virtual														// destructor
			~Plane(void);

		virtual bool
			hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

		virtual bool
			ShadowHit(const Ray&, float& tmin) const;

	private:

		glm::vec3 	point;   				// point through which plane passes 
		glm::vec3	normal;					// normal to the plane

		static const double kEpsilon;   // for shadows and secondary rays
	};
}


