#include "enpch.h"
#include "RTPinhole.h"

#include "../World/World.h"


#include "Engine/Application.h"

namespace Engine {

	void RTPinhole::render_scene(World * world)
	{
		glm::vec3 L;
		ViewPlane vp(world->vp);
		Ray ray;
		int depth = 0;
		glm::vec2 sp;
		glm::vec2 pp;

		vp.s /= m_Zoom;
		ray.o = m_Eye;

		for (int r = 0; r < vp.vres; r++)
		{
			for (int c = 0; c < vp.hres; c++)
			{
				L = black;

				for (int j = 0; j < vp.num_samples; j++)
				{
					sp = vp.sampler_ptr->sample_unit_square();
					pp.x = vp.s * (c - 0.5 * vp.hres + sp.x);
					pp.y = vp.s * (r - 0.5 * vp.vres + sp.y);

					ray.d = ray_direction(pp, vp);
					L += world->tracer_ptr->trace_ray(ray, 0);
				}

				L /= vp.num_samples;
				L *= m_ExposureTime;
				world->image->setPixel(r, c, L);
				world->set_pixel(r, c, L);
			}
		}

	}

	void RTPinhole::RenderStereo(World * world, float x, int offset)
	{
		glm::vec3 L;
		ViewPlane vp(world->vp);
		Ray ray;
		int depth = 0;
		glm::vec2 sp;
		glm::vec2 pp;

		vp.s /= m_Zoom;
		ray.o = m_Eye;

		for (int r = 0; r < vp.vres; r++)
		{
			for (int c = 0; c < vp.hres; c++)
			{
				L = black;

				for (int j = 0; j < vp.num_samples; j++)
				{
					sp = vp.sampler_ptr->sample_unit_square();
					pp.x = vp.s * (c - 0.5 * vp.hres + sp.x) + x;
					pp.y = vp.s * (r - 0.5 * vp.vres + sp.y);

					ray.d = ray_direction(pp, vp);
					L += world->tracer_ptr->trace_ray(ray, 0);
				}

				L /= vp.num_samples;
				L *= m_ExposureTime;
				world->image->setPixel(c, r + offset, L);
				world->set_pixel(r, c + offset, L);
			}
		}
	}
	glm::vec3 RTPinhole::ray_direction(const glm::vec2& p, const ViewPlane& vp) const
	{
		//TODO clean up

		float horizontal = m_Distance * tan(glm::radians(m_FOV / 2));
		float vertical = horizontal * ((float)vp.vres/(float)vp.hres);

		float x = horizontal * (2 * p.x / (float)vp.hres);
		float y = vertical * (2 * p.y / (float)vp.vres);

		glm::vec3 dir = x * m_U + y * m_V - 0.1f * m_W;
		return glm::normalize(dir);
	}
}