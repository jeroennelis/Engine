#pragma once

#include "enpch.h"

namespace Engine {

	class Mapping
	{

	public:
		virtual void GetTexelCoordinates(const glm::vec3& localHitPoint,
			const int hRes,
			const int vRes,
			int& row,
			int& column) const = 0;
	};
}
