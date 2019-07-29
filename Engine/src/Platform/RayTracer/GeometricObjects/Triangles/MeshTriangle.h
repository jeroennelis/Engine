#pragma once

#include "..//GeometricObject.h"
#include "..//..//Utilities/Mesh.h"
#include "Engine/Maths.h"

namespace Engine {

	class MeshTriangle : public GeometricObject
	{
	public:
		Mesh* mesh;
		int Index0, Index1, Index2;
		glm::vec3 Normal;
		
	public:
		MeshTriangle();
		
		MeshTriangle(Mesh* mesh_ptr, const int i0, const int i1, const int i2);

		virtual MeshTriangle* clone() const = 0;

		MeshTriangle(const MeshTriangle& mt);

		virtual ~MeshTriangle();

		MeshTriangle& operator= (const MeshTriangle& rhs);

		virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const = 0;

		virtual bool ShadowHit(const Ray& ray, float& tmin) const override;

		void ComputeNormal(const bool reverseNormal);

		virtual glm::vec3 GetNormal() const;

		virtual BBox GetBoundingBox() override;

	protected:

		float
			InterpolateU(const float beta, const float gamma) const;

		float
			InterpolateV(const float beta, const float gamma) const;
	};
}
