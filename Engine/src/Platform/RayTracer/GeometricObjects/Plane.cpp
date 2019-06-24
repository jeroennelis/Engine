#include "enpch.h"

#include "Plane.h"

namespace Engine {
	const double Plane::kEpsilon = 0.001;

	// ----------------------------------------------------------------------  default constructor

	Plane::Plane(void)
		: GeometricObject(),
		point(0.0),
		normal(0, 1, 0)
	{}


	// ----------------------------------------------------------------------  constructor

	Plane::Plane(const glm::vec3& point, const glm::vec3& n)
		: GeometricObject(),
		point(point),
		normal(n)
	{
		normal = glm::normalize(normal);
	}


	// ---------------------------------------------------------------- copy constructor

	Plane::Plane(const Plane& p)
		: GeometricObject(p),
		point(p.point),
		normal(p.normal)
	{}


	// ---------------------------------------------------------------- clone

	Plane*
		Plane::clone(void) const {
		return (new Plane(*this));
	}


	// ---------------------------------------------------------------- assignment operator

	Plane&
		Plane::operator= (const Plane& rhs) {

		if (this == &rhs)
			return (*this);

		GeometricObject::operator= (rhs);

		point = rhs.point;
		normal = rhs.normal;

		return (*this);
	}


	// ---------------------------------------------------------------- destructor

	Plane::~Plane(void)
	{}


	// ----------------------------------------------------------------- hit

	bool
		Plane::hit(const Ray& ray, double& tmin, ShadeRec& sr) const 
	{
		float t = glm::dot((point - ray.o) , normal / glm::dot(ray.d , normal));

		if (t > kEpsilon) {
			tmin = t;
			sr.normal = normal;
			sr.local_hit_point = ray.o + t * ray.d;

			return (true);
		}

		return(false);
	}
}



