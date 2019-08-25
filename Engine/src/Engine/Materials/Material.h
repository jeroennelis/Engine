#pragma once

#include "enpch.h"



namespace Engine
{
	class Texture_temp;

	class ShadeRec;

	class Material
	{
	public:

		virtual glm::vec3 Shade(ShadeRec& sr);

		virtual glm::vec3 ShadeAreaLight(ShadeRec& sr);

		virtual glm::vec3 ShadePath(ShadeRec& sr);

		virtual glm::vec3 GetLe(ShadeRec& sr) const;

		
		virtual float GetKa();
					  
		virtual float GetKd();
					  
		virtual float GetKs();
					  
		virtual float GetExp();

		virtual Texture_temp* GetCd();

	};
}