#include "enpch.h"
#include "Material.h"
#include "Engine/Textures/ConstantColor.h"

namespace Engine {
	glm::vec3 Material::Shade(ShadeRec& sr)
	{
		EN_CORE_ASSERT(false, "not implemented");
		return glm::vec3();
	}

	glm::vec3 Material::ShadeAreaLight(ShadeRec& sr)
	{
		EN_CORE_ASSERT(false, "not implemented");
		return glm::vec3();
	}

	glm::vec3 Material::ShadePath(ShadeRec& sr)
	{
		EN_CORE_ASSERT(false, "not implemented");
		return glm::vec3();
	}

	glm::vec3 Material::GetLe(ShadeRec& sr) const
	{
		EN_CORE_ASSERT(false, "not implemented");
		return glm::vec3();
	}


	float Material::GetKa()
	{
		EN_CORE_ASSERT(false, "not implemented");
		return 1.0f;
	}

	float Material::GetKd()
	{
		EN_CORE_ASSERT(false, "not implemented");
		return 0.0f;
	}

	float Material::GetKs()
	{
		EN_CORE_ASSERT(false, "not implemented");
		return 0.0f;
	}

	float Material::GetExp()
	{
		EN_CORE_ASSERT(false, "not implemented");
		return 0.0f;
	}

	Texture* Material::GetCd()
	{
		EN_CORE_ASSERT(false, "not implemented");
		return new ConstantColor();
	}
}


