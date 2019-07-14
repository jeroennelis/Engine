#include "enpch.h"
#include "FlatMeshTriangle.h"

namespace Engine {

	FlatMeshTriangle::FlatMeshTriangle()
		:MeshTriangle()
	{
	}

	FlatMeshTriangle::FlatMeshTriangle(Mesh* meshPtr, const int index0, const int index1, const int index2)
		:MeshTriangle(meshPtr, index0, index1, index2)
	{
	}

	FlatMeshTriangle* FlatMeshTriangle::clone() const
	{
		return (new FlatMeshTriangle(*this));
	}

	FlatMeshTriangle::FlatMeshTriangle(const FlatMeshTriangle& fmt)
		:MeshTriangle(fmt)
	{
	}


	FlatMeshTriangle& FlatMeshTriangle::operator=(const FlatMeshTriangle& rhs)
	{
		if (this == &rhs)
			return (*this);

		MeshTriangle::operator= (rhs);

		return (*this);
	}

	FlatMeshTriangle::~FlatMeshTriangle()
	{
	}

	bool FlatMeshTriangle::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
	{
		glm::vec3 v0(mesh->Vertices[Index0]);
		glm::vec3 v1(mesh->Vertices[Index1]);
		glm::vec3 v2(mesh->Vertices[Index2]);

		double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.d.x, d = v0.x - ray.o.x;
		double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.d.y, h = v0.y - ray.o.y;
		double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.d.z, l = v0.z - ray.o.z;

		double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
		double q = g * i - e * k, s = e * j - f * i;

		double inv_denom = 1.0 / (a * m + b * q + c * s);

		double e1 = d * m - b * n - c * p;
		double beta = e1 * inv_denom;

		if (beta < 0.0)
			return (false);

		double r = e * l - h * i;
		double e2 = a * n + d * q + c * r;
		double gamma = e2 * inv_denom;

		if (gamma < 0.0)
			return (false);

		if (beta + gamma > 1.0)
			return (false);

		double e3 = a * p - b * r + d * s;
		double t = e3 * inv_denom;

		if (t < kEpsilon)
			return (false);

		tmin = t;
		sr.normal = Normal;  				// for flat shading
		sr.local_hit_point = ray.o + (float)t * ray.d;

		return (true);
	}
}