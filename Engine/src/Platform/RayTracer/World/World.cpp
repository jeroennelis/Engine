#include "enpch.h"

#include "World.h"

#include <iostream>
#include "../Cameras/RTPinhole.h"

namespace Engine {
	World::World()
		:image(NULL)
	{
	}


	World::~World()
	{
		//delete image;
		for (GeometricObject* object : objects)
		{
			delete object;
		}
	}

	void World::build(void)
	{
		printf("building the world\n");

		int num_samples = 1024;

		vp.set_hres(300);
		vp.set_vres(300);
		vp.set_sampler(new MultiJittered(num_samples));
		vp.set_pixel_size(1);
		
		background_color = black;
		tracer_ptr = new MultipleObjects(this);


		Sphere* sphere_ptr = new Sphere(glm::vec3(0, 0, 0), 50);
		sphere_ptr->set_color(0, 1, 0);
		add_object(sphere_ptr);


		RTPinhole* pinhole_ptr = new RTPinhole();
		pinhole_ptr->SetEye(glm::vec3(0, 1, 500));
		pinhole_ptr->SetLookat(glm::vec3(0, 0, 0));
		pinhole_ptr->SetViewDistance(500);
		pinhole_ptr->compute_uvw();

		SetCamera(pinhole_ptr);

		Plane* plane_ptr = new Plane(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		plane_ptr->set_color(glm::vec3(1,0,0));
		add_object(plane_ptr);

		image = new Image(300, 300);
	}

	ShadeRec World::hit_bare_bones_objects(const Ray& ray)
	{
		ShadeRec sr(*this);
		double t;
		double tmin = kHugeValue;
		int num_objects = objects.size();

		for (int j = 0; j < num_objects; j++)
		{
			if (objects[j]->hit(ray, t, sr) && (t < tmin))
			{
				sr.hit_an_object = true;
				tmin = t;
				sr.color = objects[j]->get_color();
			}
		}
		return sr;
	}

	void World::render_scene(std::string& filename) const
	{
		if (tracer_ptr == NULL)
		{
			// TODO exit & logging
			std::cout << "tracer was not initialised" << std::endl;
			return;
		}
		printf("rendering the scene\n");
		glm::vec3	pixel_color;
		Ray			ray;
		double		zw = 100.0;

		ray.d = glm::vec3(0, 0, -1);

		int n = (int)sqrt((float)vp.num_samples);

		glm::vec2 sp;			//sample poit in [0, 1] [0, 1]
		glm::vec2 pp;			//sample point on a pixel

		for (int r = 0; r < vp.vres; r++)
		{
			for (int c = 0; c < vp.hres; c++)
			{
				pixel_color = black;

				for (int p = 0; p < n; p++)
				{
					for (int q = 0; q < n; q++)
					{
						sp = vp.sampler_ptr->sample_unit_square();
						pp.x = vp.s * (c - 0.5 * vp.hres + sp.x);
						pp.y = vp.s * (r - 0.5 * vp.vres + sp.y);
						ray.o = glm::vec3(pp.x, pp.y, zw);
						pixel_color += tracer_ptr->trace_ray(ray);
					}
				}
				pixel_color /= vp.num_samples;
				set_pixel(r, c, pixel_color);
				image->setPixel(r, c, pixel_color);

			}
		}

		int test = 0;
		image->saveImage(filename.append(".png"));
	}

	void World::render_perspective(std::string& filename) const
	{
		if (tracer_ptr == NULL)
		{
			// TODO exit & logging
			std::cout << "tracer was not initialised" << std::endl;
			return;
		}
		printf("rendering the scene\n");

		glm::vec3 pixel_color;
		Ray ray;
		float eye = 0;
		float d = 10.0;

		ray.o = glm::vec3(0, 0, eye);

		for (int r = 0; r < vp.vres; r++)
		{
			for (int c = 0; c < vp.hres; c++)
			{
				ray.d = glm::vec3(vp.s * (c - 0.5 * (vp.hres - 1.0)), vp.s * (r - 0.5 * (vp.vres - 1.0)), -d);
				ray.d = glm::normalize(ray.d);
				pixel_color = tracer_ptr->trace_ray(ray);
				set_pixel(r, c, pixel_color);
				image->setPixel(r, c, pixel_color);
			}
		}
		image->saveImage(filename.append(".png"));


	}

	void World::set_pixel(const int row, const int column, const glm::vec3& pixelColor) const
	{
		image->setPixel(row, column, pixelColor);
	}

}