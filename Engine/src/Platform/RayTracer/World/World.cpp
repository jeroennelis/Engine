#include "enpch.h"

#include "World.h"

#include <iostream>
#include "../Cameras/RTPinhole.h"
#include "../Cameras/RTFishEye.h"
#include "../Cameras/RTSpherical.h"
#include "../Cameras/RTStereoCamera.h"
#include "../Lights/RTAmbient.h"
#include "..//Tracers/RayCast.h"
#include "..//Lights/RTAmbient.h"
#include "..//Materials/RTMatte.h"
#include "..//Lights/RTPointLight.h"
#include "../Materials/RTPhong.h"
#include "Engine/Maths.h"

#include "../Lights/RTAmbientOccluder.h"


namespace Engine {
	World::World()
		:camera_ptr(NULL),
		background_color(black),
		tracer_ptr(NULL),
		ambient_ptr(new RTAmbient),
		image(NULL)
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

		vp.set_hres(1024);
		vp.set_vres(1024);
		vp.sampler_ptr = new MultiJittered(128);
		vp.num_samples = 128;

		background_color = black;
		tracer_ptr = new RayCast(this);

		RTAmbient* occluder_ptr = new RTAmbient;
		//occluder_ptr->SetSampler(vp.sampler_ptr);

		SetAmbientLight(occluder_ptr);

		RTPinhole* pinhole_ptr = new RTPinhole;
		pinhole_ptr->SetEye(glm::vec3(7.5, 4, 10));
		pinhole_ptr->SetLookat(glm::vec3(-1, 3.7, 0));
		pinhole_ptr->SetViewDistance(340);
		pinhole_ptr->compute_uvw();
		SetCamera(pinhole_ptr);

		RTPointLight* light_ptr2 = new RTPointLight;
		light_ptr2->SetLocation(glm::vec3(200, 100, 50));
		//light_ptr2->SetColor(glm::vec3(1.0, 0, 0));
		light_ptr2->SetLs(3.0);
		AddLight(light_ptr2);

		RTMatte* matte_ptr1 = new RTMatte;
		matte_ptr1->SetKa(0.25);
		matte_ptr1->SetKd(0.80);
		matte_ptr1->SetCd(glm::vec3(0.1, 0.1, 0.5));	  				// yellow

		RTPhong* phong = new RTPhong;
		phong->SetKa(0.25);
		phong->SetKd(0.75);
		phong->SetKs(0.25);
		phong->SetExp(50);
		phong->SetCd(glm::vec3(0.75, 0.75, 0));

		Sphere* sphere_ptr1 = new Sphere(glm::vec3(3.85, 2.3, -2.55), 2.3);
		sphere_ptr1->SetMaterial(phong);
		add_object(sphere_ptr1);

		RTPhong* phong2 = new RTPhong;
		phong2->SetKa(0.15);
		phong2->SetKd(0.85);
		phong2->SetKs(0.25);
		phong2->SetExp(50);
		phong2->SetCd(glm::vec3(0.71, 0.40, 0.16));

		Sphere* sphere_ptr = new Sphere(glm::vec3(-0.7, 1, 4.2), 2);
		sphere_ptr->SetMaterial(phong2);
		add_object(sphere_ptr);



		Plane* plane_ptr = new Plane(glm::vec3(0, -1, 0), glm::vec3(0, 1, 0));
		plane_ptr->SetMaterial(matte_ptr1);
		add_object(plane_ptr);

		image = new Image(1024,1024);
	}

	ShadeRec World::hit_objects(const Ray& ray)
	{
		ShadeRec sr(*this);
		double t;
		glm::vec3 normal;
		glm::vec3 local_hit_point;
		double tmin = kHugeValue;
		int num_objects = objects.size();

		for (int j = 0; j < num_objects; j++)
		{
			if (objects[j]->hit(ray, t, sr) && (t < tmin))
			{
				sr.hit_an_object = true;
				tmin = t;
				sr.material_ptr = objects[j]->GetMaterial();
				normal = sr.normal;
				local_hit_point = sr.local_hit_point;

			}
		}
		if (sr.hit_an_object)
		{
			sr.t = tmin;
			sr.normal = normal;
			sr.local_hit_point = local_hit_point;
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
		glm::vec3 mappedColor = MaxToOne(pixelColor);
		image->setPixel(row, column, mappedColor);
	}

	glm::vec3 World::MaxToOne(const glm::vec3 & c) const
	{
		float maxValue = max(c.r, max(c.g, c.b));

		if (maxValue > 1.0)
			return (c / maxValue);
		else
			return c;
	}

	glm::vec3 World::ClampToColor(const glm::vec3 & rawColor) const
	{
		glm::vec3 c(rawColor);

		if (rawColor.r > 1.0 || rawColor.g > 1.0 || rawColor.b > 0)
		{
			c.r = 1.0;
			c.g = 1.0;
			c.b = 0.0;
		}
		return c;
	}

}