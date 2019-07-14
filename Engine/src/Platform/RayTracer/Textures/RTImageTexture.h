#pragma once

#include "Engine/Textures/ImageTexture.h"
#include "Engine/image.h"
#include "..//Mapping/Mapping.h"

namespace Engine {

	class RTImageTexture : public ImageTexture
	{

	public:
		virtual glm::vec3 GetColor(const ShadeRec& sr) const override;

		inline void SetImage(Image* image) { m_Image = image; }
		inline void SetMapping(Mapping* mapping) { m_Mapping = mapping; }

	private:
		Image* m_Image;
		Mapping* m_Mapping;

		// Inherited via ImageTexture
	};
}