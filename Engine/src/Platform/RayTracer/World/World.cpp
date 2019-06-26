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

		int num_samples = 256;

		vp.set_hres(400);
		vp.set_vres(400);
		vp.set_pixel_size(1);
		vp.sampler_ptr = new MultiJittered(16);
		vp.num_samples = 16;

		background_color = black;
		tracer_ptr = new RayCast(this);

		RTAmbient* ambient_ptr = new RTAmbient;
		ambient_ptr->SetLs(1.0);
		SetAmbientLight(ambient_ptr);

		RTPinhole* pinhole_ptr = new RTPinhole;
		pinhole_ptr->SetEye(glm::vec3(0, 0, 500));
		pinhole_ptr->SetLookat(glm::vec3(-5, 0, 0));
		pinhole_ptr->SetViewDistance(850.0);
		pinhole_ptr->compute_uvw();
		SetCamera(pinhole_ptr);

		RTPointLight* light_ptr2 = new RTPointLight;
		light_ptr2->SetLocation(glm::vec3(100, 50, 150));
		//light_ptr2->SetColor(glm::vec3(1.0, 0, 0));
		light_ptr2->SetLs(3.0);
		AddLight(light_ptr2);

		RTMatte* matte_ptr1 = new RTMatte;
		matte_ptr1->SetKa(0.25);
		matte_ptr1->SetKd(0.65);
		matte_ptr1->SetCd(glm::vec3(1, 1, 0));	  				// yellow	
		Sphere* sphere_ptr1 = new Sphere(glm::vec3(10, -5, 0), 27);
		sphere_ptr1->SetMaterial(matte_ptr1);
		add_object(sphere_ptr1);

		RTMatte* matteptr2 = new RTMatte;
		matteptr2->SetKa(0.15);
		matteptr2->SetKd(0.85);
		matteptr2->SetCd(glm::vec3(0.71, 0.40, 0.16));

		Sphere* sphere_ptr = new Sphere(glm::vec3(-25, 10, -35), 27);
		sphere_ptr->SetMaterial(matteptr2);
		add_object(sphere_ptr);

		//Sphere* sphere_ptr2 = new Sphere(glm::vec3(-50, 0, 0), 50);
		//sphere_ptr2->set_color(1, 0, 0);
		//add_object(sphere_ptr2);

		//float vpd = 100;

		//RTPinhole *leftCam = new RTPinhole();
		//leftCam->SetViewDistance(vpd);
		//RTPinhole *rightCam = new RTPinhole();
		//rightCam->SetViewDistance(vpd);

		//RTStereoCamera* stereoCam = new RTStereoCamera;
		//stereoCam->SetLeftCamera(leftCam);
		//stereoCam->SetRightCamera(rightCam);
		//stereoCam->UseParallelViewing();
		//stereoCam->SetPixelGap(5);
		//stereoCam->SetEye(glm::vec3(5, 0, 100));
		//stereoCam->SetLookat(glm::vec3(0.0));
		//stereoCam->compute_uvw();
		//stereoCam->SetStereoAngle(5);
		//stereoCam->SetUpCameras();
		//SetCamera(stereoCam);


		///*Plane* plane_ptr = new Plane(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		//plane_ptr->set_color(glm::vec3(1,0,0));
		//add_object(plane_ptr);*/

		image = new Image(400,400);
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
		image->setPixel(row, column, pixelColor);
	}

}