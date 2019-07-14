#pragma once

#include "Mapping.h"

namespace Engine {

	class SphericalMap : public Mapping
	{
	public:
		virtual void GetTexelCoordinates(const glm::vec3& localHitPoint, const int hRes, const int vRes, int& row, int& column) const override;

	};
}