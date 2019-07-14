#include "enpch.h"
#include "Triangle.h"

namespace Engine {

	// --------------------------------------------------------------------- Default Constructor
	Triangle::Triangle()
		: GeometricObject(),
		V0(0,0,0),
		V1(0,0,1),
		V2(1,0,0),
		Normal(0,1,0)
	{
	}

	// --------------------------------------------------------------------- Constructor
	Triangle::Triangle(const glm::vec3& v0, glm::vec3& v1, glm::vec3& v2)
		: GeometricObject(),
		V0(v0),
		V1(v1),
		V2(v2)
	{
		ComputeNormal();
	}

	// --------------------------------------------------------------------- Clone
	Triangle* Triangle::clone() const
	{
		return (new Triangle(*this));
	}

	// --------------------------------------------------------------------- Copy Constructor
	Triangle::Triangle(const Triangle& triangle)
		: GeometricObject(triangle),
		V0(triangle.V0),
		V1(triangle.V1),
		V2(triangle.V2),
		Normal(triangle.Normal)
	{
	}

	// --------------------------------------------------------------------- Assignment Operator
	Triangle& Triangle::operator=(const Triangle& rhs)
	{
		if (this == &rhs)
			return (*this);

		GeometricObject::operator=(rhs);

		V0 = rhs.V0;
		V1 = rhs.V1;
		V2 = rhs.V2;
		Normal = rhs.Normal;

		return (*this);
	}

	BBox Triangle::GetBoundingBox()
	{
		double delta = 0.000001;

		return (BBox(min(min(V0.x, V1.x), V2.x) - delta, max(max(V0.x, V1.x), V2.x) + delta,
			min(min(V0.y, V1.y), V2.y) - delta, max(max(V0.y, V1.y), V2.y) + delta,
			min(min(V0.z, V1.z), V2.z) - delta, max(max(V0.z, V1.z), V2.z) + delta));
	}

	void Triangle::ComputeNormal()
	{
		Normal = glm::cross((V1 - V0), (V2 - V0));
		Normal = glm::normalize(Normal);
	}

	// --------------------------------------------------------------------- Hit
	// Check if ray hits the triangle
	// using barycentric coordinates
	bool Triangle::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
	{
		double a = V0.x - V1.x, b = V0.x - V2.x, c = ray.d.x, d = V0.x - ray.o.x;
		double e = V0.y - V1.y, f = V0.y - V2.y, g = ray.d.y, h = V0.y - ray.o.y;
		double i = V0.z - V1.z, j = V0.z - V2.z, k = ray.d.z, l = V0.z - ray.o.z;

		double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
		double q = g * i - e * k, s = e * j - f * i;

		double invDenom = 1.0 / (a * m + b * q + c * s);

		double e1 = d * m - b * n - c * p;
		double beta = e1 * invDenom;

		if (beta < 0.0)
			return false;

		double r = e * l - h * i;
		double e2 = a * n + d * q + c * r;
		double gamma = e2 * invDenom;

		if (gamma < 0.0)
			return (false);

		if (beta + gamma > 1.0)
			return (false);

		double e3 = a * p - b * r + d * s;
		double t = e3 * invDenom;

		if (t < kEpsilon)
			return (false);

		tmin = t;
		sr.normal = Normal;
		sr.local_hit_point = ray.o + (float)t* ray.d;

		return (true);
	}

	bool Triangle::ShadowHit(const Ray& ray, float& tmin) const
	{
		double a = V0.x - V1.x, b = V0.x - V2.x, c = ray.d.x, d = V0.x - ray.o.x;
		double e = V0.y - V1.y, f = V0.y - V2.y, g = ray.d.y, h = V0.y - ray.o.y;
		double i = V0.z - V1.z, j = V0.z - V2.z, k = ray.d.z, l = V0.z - ray.o.z;

		double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
		double q = g * i - e * k, s = e * j - f * i;

		double invDenom = 1.0 / (a * m + b * q + c * s);

		double e1 = d * m - b * n - c * p;
		double beta = e1 * invDenom;

		if (beta < 0.0)
			return (false);

		double r = e * l - h * i;
		double e2 = a * n + d * q + c * r;
		double gamma = e2 * invDenom;

		if (gamma < 0.0)
			return (false);

		if (beta + gamma > 1.0)
			return (false);

		double e3 = a * p - b * r + d * s;
		double t = e3 * invDenom;

		if (t < kEpsilon)
			return (false);

		tmin = t;

		return(true);
	}

}

