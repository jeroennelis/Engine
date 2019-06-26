#include "enpch.h"
#include "RTMaterial.h"

#include "..//World/World.h"


namespace Engine {
	RTMaterial::RTMaterial()
	{
	}

	RTMaterial::~RTMaterial()
	{
	}

	glm::vec3 RTMaterial::Shade(ShadeRec& sr)
	{
		EN_CORE_ASSERT(false, "not implemented");
		return black;
	}

	glm::vec3 RTMaterial::ShadeAreaLight(ShadeRec& sr)
	{
		EN_CORE_ASSERT(false, "not implemented");
		return black;
	}

	glm::vec3 RTMaterial::ShadePath(ShadeRec& sr)
	{
		EN_CORE_ASSERT(false, "not implemented");
		return black;
	}
}