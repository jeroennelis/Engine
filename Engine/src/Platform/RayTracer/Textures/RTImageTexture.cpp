#include "enpch.h"
#include "RTImageTexture.h"

namespace Engine {

	glm::vec3 RTImageTexture::GetColor(const ShadeRec& sr) const
	{
		int row, column;

		if (m_Mapping)
		{
			m_Mapping->GetTexelCoordinates(sr.local_hit_point, m_Image->getWidth(), m_Image->getHeight(), row, column);
		}
		else
		{
			row = (int)(sr.v * (m_Image->getHeight() - 1));
			column = (int)(sr.u * (m_Image->getWidth() - 1));
		}

		return m_Image->GetColor(row, column);
	}
}