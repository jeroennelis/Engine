#include "enpch.h"
#include "SmoothMeshTriangle.h"

namespace Engine {
	
	SmoothMeshTriangle::SmoothMeshTriangle()
		:MeshTriangle()
	{
	}

	SmoothMeshTriangle::SmoothMeshTriangle(Mesh* meshPtr, const int i0, const int i1, const int i2)
		:MeshTriangle(meshPtr, i0 , i1, i2)
	{
	}

	SmoothMeshTriangle* SmoothMeshTriangle::clone() const
	{
		return new SmoothMeshTriangle(*this);
	}

	SmoothMeshTriangle::SmoothMeshTriangle(const SmoothMeshTriangle& smt)
		:MeshTriangle(smt)
	{
	}

	SmoothMeshTriangle::~SmoothMeshTriangle()
	{
	}

	SmoothMeshTriangle& SmoothMeshTriangle::operator=(const SmoothMeshTriangle& rhs)
	{
		if (this == &rhs)
			return (*this);

		MeshTriangle::operator= (rhs);

		return (*this);
	}

	bool SmoothMeshTriangle::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
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
		sr.normal = InterpolateNormal(beta, gamma); // for smooth shading
		sr.local_hit_point = ray.o + (float)t * ray.d;

		return (true);
	}

	glm::vec3 SmoothMeshTriangle::InterpolateNormal(const float beta, const float gamma) const
	{
		glm::vec3 normal((1 - beta - gamma) * mesh->Normals[Index0]
			+ beta * mesh->Normals[Index1]
			+ gamma * mesh->Normals[Index2]);
		normal = glm::normalize(normal);

		return(normal);
	}
}


