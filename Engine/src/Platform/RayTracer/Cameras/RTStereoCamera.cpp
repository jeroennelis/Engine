#include "enpch.h"
#include "RTStereoCamera.h"

#include "../World/World.h"

namespace Engine {
	RTStereoCamera::RTStereoCamera()
		:m_Viewing(parallel), m_PixelGap(10), m_Beta(0.75)
	{

	}

	RTStereoCamera::~RTStereoCamera()
	{
	}

	void RTStereoCamera::SetUpCameras()
	{
		double r = glm::distance(m_Eye, m_Lookat);
		float x = r * tan(0.5 * m_Beta * PI_ON_180);

		m_LeftCamera->SetEye(m_Eye - x * m_U);
		m_LeftCamera->SetLookat(m_Lookat - x * m_U);
		m_LeftCamera->compute_uvw();

		m_RightCamera->SetEye(m_Eye + x * m_U);
		m_RightCamera->SetLookat(m_Lookat + x * m_U);
		m_RightCamera->compute_uvw();
	}

	void RTStereoCamera::render_scene(World * world)
	{
		ViewPlane vp = world->vp;
		int hres = vp.hres;
		int vres = vp.vres;

		double r = glm::distance(m_Eye, m_Lookat);
		double x = r * tan(0.5 * m_Beta * PI_ON_180);

		if (m_Viewing == parallel)
		{
			m_LeftCamera->RenderStereo(world, x, 0);
			m_RightCamera->RenderStereo(world, -x, hres + m_PixelGap);
		}

		if (m_Viewing == transverse)
		{
			m_LeftCamera->RenderStereo(world, x, hres + m_PixelGap);
			m_RightCamera->RenderStereo(world, x, 0);
		}
	}

	void RTStereoCamera::RenderStereo(World * world, float x, int offset)
	{
		render_scene(world);
	}
}


