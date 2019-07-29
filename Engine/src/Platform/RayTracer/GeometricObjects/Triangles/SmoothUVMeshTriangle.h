#pragma once

#include "SmoothMeshTriangle.h"

namespace Engine {

	class SmoothUVMeshTriangle : public SmoothMeshTriangle
	{
	public:
		SmoothUVMeshTriangle(Mesh* meshPtr, const int i0, const int i1, const int i2);

		virtual bool hit(const Ray& ray, double& tmin, ShadeRec& st) const override;
	};
}

