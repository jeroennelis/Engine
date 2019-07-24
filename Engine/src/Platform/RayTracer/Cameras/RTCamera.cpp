#include "enpch.h"

#include "RTCamera.h"

#include "../World/World.h"

namespace Engine {

	RTCamera::RTCamera()
		:	m_Eye(0, 0, 500),
			m_Lookat(0),
			
			m_Up(0, 1, 0),
			m_U(1, 0, 0),
			m_V(0, 1, 0),
			m_W(0, 0, 1),
			m_ExposureTime(1.0)
	{}
	
	void RTCamera::compute_uvw(void)
	{
		m_W = glm::normalize(/*m_Eye*/ - m_Lookat);
		m_U= glm::normalize(glm::cross(m_Up, m_W));
		m_V = glm::cross(m_W, m_U);
	}

}