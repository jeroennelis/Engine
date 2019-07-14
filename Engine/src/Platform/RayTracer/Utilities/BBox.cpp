#include "enpch.h"
#include "BBox.h"

namespace Engine {

	// ---------------------------------------------------------------- default constructor
	BBox::BBox()
		:X0(-1), X1(1), Y0(-1), Y1(1), Z0(-1), Z1(1)
	{
	}

	// ---------------------------------------------------------------- constructor
	BBox::BBox(const double& x0, const double& x1, const double& y0, const double& y1, const double& z0, const double& z1)
		: X0(x0), X1(x1), Y0(y0), Y1(y1), Z0(z0), Z1(z1)
	{
	}

	// ---------------------------------------------------------------- copy constructor
	BBox::BBox(const BBox& bBox)
		: X0(bBox.X0), X1(bBox.X1), Y0(bBox.Y0), Y1(bBox.Y1), Z0(bBox.Z0), Z1(bBox.Z1)
	{
	}

	// ---------------------------------------------------------------- assignment operator
	BBox& BBox::operator=(const BBox& rhs)
	{
		if (this == &rhs)
			return (*this);
		X0 = rhs.X0;
		X1 = rhs.X1;
		Y0 = rhs.Y0;
		Y1 = rhs.Y1;
		Z0 = rhs.Z0;
		Z1 = rhs.Z1;
	}

	// ---------------------------------------------------------------- destructor
	BBox::~BBox()
	{
	}

	// ---------------------------------------------------------------- hit
	// Check if the ray hits the Bounding Box
	bool BBox::Hit(const Ray& ray) const
	{
		double ox = ray.o.x;
		double oy = ray.o.y;
		double oz = ray.o.z;

		double dx = ray.d.x;
		double dy = ray.d.y;
		double dz = ray.d.z;

		double txMin, tyMin, tzMin;
		double txMax, tyMax, tzMax;

		double a = 1.0 / dx;
		if (a >= 0)
		{
			txMin = (X0 - ox) * a;
			txMax = (X1 - ox) * a;
		}
		else
		{
			txMin = (X1 - ox) * a;
			txMax = (X0 - ox) * a;
		}

		double b = 1.0 / dy;
		if (b >= 0)
		{
			tyMin = (Y0 - oy) * b;
			tyMax = (Y1 - oy) * b;
		}
		else
		{
			txMin = (Y1 - oy) * b;
			txMax = (Y0 - oy) * b;
		}

		double c = 1.0 / dz;
		if (c >= 0)
		{
			tzMin = (Z0 - oz) * c;
			tzMax = (Z1 - oz) * c;
		}
		else
		{
			tzMin = (Z1 - oz) * c;
			tzMax = (Z0 - oz) * c;
		}

		double t0, t1;

		// find largest entering t value

		if (txMin > tyMin)
			t0 = txMin;
		else
			t0 = tyMin;

		if (tzMin > t0)
			t0 = tzMin;

		// find smallest exiting t value

		if (txMax < tyMax)
			t1 = txMax;
		else
			t1 = tyMax;

		if (tzMax < t1)
			t1 = tzMax;

		return (t0 < t1 && t1 > kEpsilon);
	}

	// ---------------------------------------------------------------- hit
	// Check if the point is inside the Bounding Box
	bool BBox::Inside(const glm::vec3& p) const
	{
		return ((p.x > X0 && p.x < X1) && (p.y > Y0 && p.y < Y1) && (p.z > Z0 && p.z < Z1));
	}



}


