#include "enpch.h"
#include "MeshTriangle.h"

namespace Engine {

	MeshTriangle::MeshTriangle()
		:GeometricObject(),
		mesh(nullptr),
		Index0(0), Index1(0), Index2(0),
		Normal(0.0)
	{
	}

	MeshTriangle::MeshTriangle(Mesh* mesh_ptr, const int i0, const int i1, const int i2)
		:GeometricObject(),
		mesh(mesh_ptr),
		Index0(i0), Index1(i1), Index2(i2)
	{
	}

	MeshTriangle::MeshTriangle(const MeshTriangle& mt)
		:GeometricObject(),
		mesh(mt.mesh),
		Index0(mt.Index0), Index1(mt.Index1), Index2(mt.Index2),
		Normal(mt.Normal)
	{
	}

	MeshTriangle::~MeshTriangle()
	{
		/*if (mesh)
		{
			delete mesh;
			mesh = nullptr;
		}*/
	}

	MeshTriangle& MeshTriangle::operator=(const MeshTriangle& rhs)
	{
		if (this == &rhs)
			return(*this);
		GeometricObject::operator=(rhs);

		mesh = rhs.mesh;
		Index0 = rhs.Index0;
		Index1 = rhs.Index1;
		Index2 = rhs.Index2;
		Normal = rhs.Normal;
	}

	bool MeshTriangle::ShadowHit(const Ray& ray, float& tmin) const
	{
		glm::vec3 v0(mesh->Vertices[Index0]);
		glm::vec3 v1(mesh->Vertices[Index1]);
		glm::vec3 v2(mesh->Vertices[Index2]);

		double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.d.x, d = v0.x - ray.o.x;
		double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.d.y, h = v0.y - ray.o.y;
		double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.d.z, l = v0.z - ray.o.z;

		double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
		double q = g * i - e * k, s = e * j - f * i;

		double invDenom = 1.0 / (a * m + b * q + c * s);

		double e1 = d * m - b * n - c * p;
		double beta = e1 * invDenom;

		if (beta < 0.0)
			return (false);

		double r = r = e * l - h * i;
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

		return (true);
	}

	void MeshTriangle::ComputeNormal(const bool reverseNormal)
	{
		Normal = glm::cross((mesh->Vertices[Index1] - mesh->Vertices[Index0]),
			(mesh->Vertices[Index2] - mesh->Vertices[Index0]));
		Normal =glm::normalize(Normal);

		if (reverseNormal)
			Normal = -Normal;
	}

	glm::vec3 MeshTriangle::GetNormal() const
	{
		return Normal;
	}

	BBox MeshTriangle::GetBoundingBox()
	{
		double delta = 0.01;  // to avoid degenerate bounding boxes

		glm::vec3 v0(mesh->Vertices[Index0]);
		glm::vec3 v1(mesh->Vertices[Index1]);
		glm::vec3 v2(mesh->Vertices[Index2]);

		return(BBox(min(min(v0.x, v1.x), v2.x) - delta, max(max(v0.x, v1.x), v2.x) + delta,
			min(min(v0.y, v1.y), v2.y) - delta, max(max(v0.y, v1.y), v2.y) + delta,
			min(min(v0.z, v1.z), v2.z) - delta, max(max(v0.z, v1.z), v2.z) + delta));
	}

	float MeshTriangle::InterpolateU(const float beta, const float gamma) const
	{
		return((1 - beta - gamma) * mesh->U[Index0]
			+ beta * mesh->U[Index1]
			+ gamma * mesh->U[Index2]);
	}

	float MeshTriangle::InterpolateV(const float beta, const float gamma) const
	{
		return((1 - beta - gamma) * mesh->V[Index0]
			+ beta * mesh->V[Index1]
			+ gamma * mesh->V[Index2]);
	}
}


