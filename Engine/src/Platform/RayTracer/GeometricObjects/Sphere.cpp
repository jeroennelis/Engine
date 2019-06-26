// This file contains the definition of the class sphere
#include "enpch.h"

#include "Sphere.h"
#include "math.h"

namespace Engine {
	const double Sphere::kEpsilon = 0.001;

	// ---------------------------------------------------------------- default constructor

	Sphere::Sphere(void)
		: GeometricObject(),
		center(0.0),
		radius(1.0)
	{}


	// ---------------------------------------------------------------- constructor

	Sphere::Sphere(glm::vec3 c, double r)
		: GeometricObject(),
		center(c),
		radius(r)
	{}


	// ---------------------------------------------------------------- clone

	Sphere*
		Sphere::clone(void) const {
		return (new Sphere(*this));
	}


	// ---------------------------------------------------------------- copy constructor

	Sphere::Sphere(const Sphere& sphere)
		: GeometricObject(sphere),
		center(sphere.center),
		radius(sphere.radius)
	{}



	// ---------------------------------------------------------------- assignment operator

	Sphere&
		Sphere::operator= (const Sphere& rhs)
	{
		if (this == &rhs)
			return (*this);

		GeometricObject::operator= (rhs);

		center = rhs.center;
		radius = rhs.radius;

		return (*this);
	}


	// ---------------------------------------------------------------- destructor

	Sphere::~Sphere(void) {}


	//---------------------------------------------------------------- hit

	bool
		Sphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
		double 		t;
		glm::vec3	temp = ray.o - center;
		double 		a = glm::dot(ray.d, ray.d);
		double 		b = 2.0 * glm::dot(temp, ray.d);
		double 		c = glm::dot(temp, temp) - radius * radius;
		double 		disc = b * b - 4.0 * a * c;

		if (disc < 0.0)
			return(false);
		else {
			double e = sqrt(disc);
			double denom = 2.0 * a;
			t = (-b - e) / denom;    // smaller root

			if (t > kEpsilon) {
				tmin = t;
				sr.normal = (temp + ray.d * (float)t) / (float)radius;
				sr.local_hit_point = ray.o + (float)t * ray.d;
				return (true);
			}

			t = (-b + e) / denom;    // larger root

			if (t > kEpsilon) {
				tmin = t;
				sr.normal = (temp + (float)t * ray.d) / (float)radius;
				sr.local_hit_point = ray.o + (float)t * ray.d;
				return (true);
			}
		}

		return (false);
	}
}