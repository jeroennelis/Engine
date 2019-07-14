#include "enpch.h"
#include "SphericalMap.h"
#include "../Utilities/Constants.h"

namespace Engine {

	void SphericalMap::GetTexelCoordinates(const glm::vec3& localHitPoint, const int hRes, const int vRes, int& row, int& column) const
	{
		float theta = acos(localHitPoint.y);
		float phi = atan2(localHitPoint.x, localHitPoint.z);

		if (phi < 0.0)
			phi += TWO_PI;

		float u = phi * invTWO_PI;
		float v = 1 - theta * invPI;

		column = (int)((hRes - 1) * u);
		row = (int)((vRes - 1) * v);
	}
}