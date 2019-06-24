#include "enpch.h"
#include "RTPinhole.h"

#include "../World/World.h"

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

					ray.d = ray_direction(pp);
					L += world->tracer_ptr->trace_ray(ray);
				}

				L /= vp.num_samples;
				L *= m_ExposureTime;
				world->image->setPixel(r, c, L);
				world->set_pixel(r, c, L);
			}
		}

	}

	glm::vec3 RTPinhole::ray_direction(const glm::vec2 & p) const
	{
		glm::vec3 dir = p.x * m_U + p.y * m_V - m_Distance * m_W;
		dir = glm::normalize(dir);

		return dir;
	}
}