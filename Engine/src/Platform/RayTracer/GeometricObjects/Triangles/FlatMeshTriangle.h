#pragma once

#include "MeshTriangle.h"

namespace Engine {

	class FlatMeshTriangle : public MeshTriangle
	{

	public:

		FlatMeshTriangle();

		FlatMeshTriangle(Mesh* meshPtr, const int index0, const int index1, const int index2);

		virtual FlatMeshTriangle* clone() const;

		FlatMeshTriangle(const FlatMeshTriangle& fmt);

		FlatMeshTriangle& operator= (const FlatMeshTriangle& rhs);

		virtual ~FlatMeshTriangle();

		virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
	};
}
