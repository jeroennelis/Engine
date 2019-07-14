#pragma once

#include "MeshTriangle.h"

namespace Engine {

	class SmoothMeshTriangle : public MeshTriangle
	{
	public:
		SmoothMeshTriangle();

		SmoothMeshTriangle(Mesh* meshPtr, const int i0, const int i1, const int i2);

		virtual SmoothMeshTriangle* clone() const override;

		SmoothMeshTriangle(const SmoothMeshTriangle& smt);

		virtual ~SmoothMeshTriangle();

		SmoothMeshTriangle& operator= (const SmoothMeshTriangle& rhs);

		virtual bool hit(const Ray& ray, double& tmin, ShadeRec& st) const override;

	protected:
		glm::vec3 InterpolateNormal(const float beta, const float gamma) const;
	};
}

