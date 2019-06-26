#include "enpch.h"

#include "RTFishEye.h"

#include "../World/World.h"

namespace Engine {

	RTFishEye::RTFishEye()
		:RTCamera(), m_PSIMax(10)
	{
	}

	RTFishEye::~RTFishEye()
	{
	}

	glm::vec3 RTFishEye::RayDirection(const glm::vec2 & pp, const int hres, const int vres, const float s, float & r_squared) const
	{
		glm::vec2 pn(2.0 / (s*hres)*pp.x, 2.0 / (s*vres)*pp.y);
		r_squared = pn.x * pn.x + pn.y * pn.y;

		if (r_squared <= 1.0)
		{
			float r = sqrt(r_squared);
			float psi = r * m_PSIMax * PI_ON_180;
			float sin_psi = sin(psi);
			float cos_psi = cos(psi);
			float sin_alpha = pn.y / r;
			float cos_alpha = pn.x / r;
			glm::vec3 dir = sin_psi * cos_alpha * m_U + sin_psi * sin_alpha * m_V - cos_psi * m_W;

			return dir;
		}
		else
			return glm::vec3(0.0);
	}

	void RTFishEye::render_scene(World * world)
	{
		glm::vec3 L;
		ViewPlane vp(world->vp);
		int hres = vp.hres;
		int vres = vp.vres;
		float s = vp.s;
		Ray ray;
		int depth = 0;
		glm::vec2 sp;
		glm::vec2 pp;
		float r_squared;

		ray.o = m_Eye;

		for (int r = 0; r < vres; r++)
		{
			for (int c = 0; c < hres; c++)
			{
				L = black;

				for (int j = 0; j < vp.num_samples; j++)
				{
					sp = vp.sampler_ptr->sample_unit_square();
					pp.x = s * (c - 0.5 * hres + sp.x);
					pp.y = s * (r - 0.5 * vres + sp.y);
					ray.d = RayDirection(pp, hres, vres, s, r_squared);
					
					if (r_squared <= 1.0)
						L += world->tracer_ptr->trace_ray(ray,0);
				}

				L /= vp.num_samples;
				L *= m_ExposureTime;
				world->image->setPixel(r, c, L);
				world->set_pixel(r, c, L);
			}
		}
	}

	void RTFishEye::RenderStereo(World * world, float x, int offset)
	{
		glm::vec3 L;
		ViewPlane vp(world->vp);
		int hres = vp.hres;
		int vres = vp.vres;
		float s = vp.s;
		Ray ray;
		int depth = 0;
		glm::vec2 sp;
		glm::vec2 pp;
		float r_squared;

		ray.o = m_Eye;

		for (int r = 0; r < vres; r++)
		{
			for (int c = 0; c < hres; c++)
			{
				L = black;

				for (int j = 0; j < vp.num_samples; j++)
				{
					sp = vp.sampler_ptr->sample_unit_square();
					pp.x = s * (c - 0.5 * hres + sp.x) + x;
					pp.y = s * (r - 0.5 * vres + sp.y);
					ray.d = RayDirection(pp, hres, vres, s, r_squared);

					if (r_squared <= 1.0)
						L += world->tracer_ptr->trace_ray(ray);
				}

				L /= vp.num_samples;
				L *= m_ExposureTime;
				world->image->setPixel(r, c + offset, L);
				world->set_pixel(r, c + offset, L);
			}
		}
	}
}