#include "enpch.h"
#include "RTSpherical.h"

#include "../World/World.h"

namespace Engine {
	RTSpherical::RTSpherical()
		:RTCamera(), m_LambdaMax(180), m_PSIMax(120)
	{
	}
	RTSpherical::~RTSpherical()
	{
	}
	glm::vec3 RTSpherical::RayDirection(const glm::vec2 pp, const int hres, const int vres, const float s) const
	{
		glm::vec2 pn(2.0 / (s*hres) * pp.x, 2.0 / (s*vres)*pp.y);

		float lambda = pn.x * m_LambdaMax * PI_ON_180;
		float psi = pn.y * m_PSIMax * PI_ON_180;

		float phi = PI - lambda;
		float theta = 0.5 * PI - psi;

		float sin_phi = sin(phi);
		float cos_phi = cos(phi);
		float sin_theta = sin(theta);
		float cos_theta = cos(theta);

		glm::vec3 dir = sin_theta * sin_phi * m_U + cos_theta * m_V + sin_theta * cos_phi * m_W;

		return dir;
	}
	void RTSpherical::render_scene(World * world)
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
					ray.d = RayDirection(pp, hres, vres, s);

					L += world->tracer_ptr->trace_ray(ray);
				}

				L /= vp.num_samples;
				L *= m_ExposureTime;
				world->image->setPixel(r, c, L);
				world->set_pixel(r, c, L);
			}
		}
	}

	void RTSpherical::RenderStereo(World * world, float x, int offset)
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
					ray.d = RayDirection(pp, hres, vres, s);

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

