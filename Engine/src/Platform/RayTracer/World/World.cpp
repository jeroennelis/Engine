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

#include "..//Materials/RTEmissive.h"
#include "..//GeometricObjects/Rectangle.h"
#include "..//Lights/RTAreaLight.h"
#include "..//Tracers/AreaLighting.h"

#include "../Lights/RTAmbientOccluder.h"

#include "..//GeometricObjects/Triangles/FlatMeshTriangle.h"
#include "..//GeometricObjects/Triangles/SmoothMeshTriangle.h"

#include "..//GeometricObjects/Grid.h"

#include "..//GeometricObjects/Instance.h"

#include "Engine/Logic/Scene.h"

#include "Platform/OpenGl/MeshRenderer.h"

#include "..//Materials/RTReflective.h"
#include "..//Tracers/Whitted.h"

#include "..//Textures/RTImageTexture.h"

#include "..//Mapping/SphericalMap.h"

#include "Engine/Materials/Material.h"

#include "Platform/OpenGl/Materials/OpenGLPhong.h"

#include "Engine/Application.h"
#include "..//GeometricObjects/Triangles/SmoothUVMeshTriangle.h"

namespace Engine {
	World::World()
		:camera_ptr(NULL),
		background_color(black),
		tracer_ptr(NULL),
		ambient_ptr(new RTAmbient),
		image(NULL)
	{
	}

	struct Vertex
	{
		glm::vec3 Position;
		int TextureIndex;
		int NormalIndex;
		Vertex* DuplicateVertex;
		int Index;
		float Length;

		Vertex(int index, glm::vec3& position);

		bool IsSet();
		bool HasSameTextureAndNormal(int textureIndexOther, int normalIndexOther);
	};


	World::~World()
	{
		//delete image;
		for (GeometricObject* object : objects)
		{
			delete object;
		}
		delete image;
	}

	std::vector<std::string> SplitString(const std::string& s, char delim)
	{
		std::vector<std::string> elems;

		const char* cstr = s.c_str();
		unsigned int strLength = (unsigned int)s.length();
		unsigned int start = 0;
		unsigned int end = 0;

		while (end <= strLength)
		{
			while (end <= strLength)
			{
				if (cstr[end] == delim)
					break;
				end++;
			}
			elems.push_back(s.substr(start, end - start));
			start = end + 1;
			end = start;
		}

		return elems;
	}

	void dealWithAlreadyProcessedVertex(Vertex* previousVertex, int newTextureIndex, int newNormalIndex, std::vector<unsigned int>& indices, std::vector<Vertex*>& vertices)
	{
		if (previousVertex->HasSameTextureAndNormal(newTextureIndex, newNormalIndex))
			indices.push_back(previousVertex->Index);
		else
		{

			Vertex* anotherVertex = previousVertex->DuplicateVertex;
			if (anotherVertex != NULL)
				dealWithAlreadyProcessedVertex(anotherVertex, newTextureIndex, newNormalIndex, indices, vertices);
			else
			{
				Vertex* duplicateVertex = new Vertex((int)vertices.size(), previousVertex->Position);
				duplicateVertex->TextureIndex = newTextureIndex;
				duplicateVertex->NormalIndex = newNormalIndex;
				previousVertex->DuplicateVertex = duplicateVertex;
				vertices.push_back(duplicateVertex);
				indices.push_back(duplicateVertex->Index);
			}

		}
	}

	void processVertex(std::vector<std::string>& vertex, std::vector<Vertex*>& vertices, std::vector<unsigned int>& indices)
	{
		int index = atoi(vertex[0].c_str()) - 1;

		Vertex* currentVertex = vertices[index];
		int textureIndex = atoi(vertex[1].c_str()) - 1;
		int normalIndex = atoi(vertex[2].c_str()) - 1;

		if (!currentVertex->IsSet())
		{
			currentVertex->TextureIndex = textureIndex;
			currentVertex->NormalIndex = normalIndex;

			indices.push_back(index);
		}
		else
			dealWithAlreadyProcessedVertex(currentVertex, textureIndex, normalIndex, indices, vertices);
	}

	void removeUnusedVertices(std::vector<Vertex*>& vertices)
	{
		for (Vertex* vertex : vertices)
		{
			if (!vertex->IsSet())
			{
				vertex->TextureIndex = 0;
				vertex->NormalIndex = 0;
			}
		}
	}

	void convertDataToVectors(std::vector<Vertex*>& vertices, std::vector<glm::vec2>& textures, std::vector<glm::vec3>& normals, std::vector<float>& verticesVector, std::vector<float>& texturesVector, std::vector<float>& normalsVector)
	{
		for (Vertex* vertex : vertices)
		{
			glm::vec3 position = vertex->Position;
			if (textures.size())
			{
				glm::vec2 textureCoord = textures[vertex->TextureIndex];
				texturesVector.push_back(textureCoord.x);
				texturesVector.push_back(1 - textureCoord.y);
			}

			glm::vec3 normalVector = normals[vertex->NormalIndex];
			verticesVector.push_back(position.x);
			verticesVector.push_back(position.y);
			verticesVector.push_back(position.z);

			normalsVector.push_back(normalVector.x);
			normalsVector.push_back(normalVector.y);
			normalsVector.push_back(normalVector.z);
		}
	}

	Instance* CreateMesh(const std::string& path, Material* mat)
	{
		Grid* grid = new Grid;

		std::ifstream file(path);
		std::vector<Vertex*> vertices;
		std::vector<glm::vec2> textures;
		std::vector<glm::vec3> normals;
		std::vector<unsigned int> indices;


		std::string line;
		if (!file.is_open())
		{
			std::cout << "file: " << path << "could not be opened!" << std::endl;
			exit(0);
		}

		while (file.good())
		{
			const char* lineCStr = line.c_str();

			getline(file, line);
			if (lineCStr[0] == 'v')
			{
				if (lineCStr[1] == 't')
				{
					std::vector<std::string> currentLine = SplitString(line, ' ');
					glm::vec2 newTexture(strtof((currentLine[1]).c_str(), 0), strtof(currentLine[2].c_str(), 0));

					textures.push_back(newTexture);
				}
				else if (lineCStr[1] == 'n')
				{
					std::vector<std::string> currentLine = SplitString(line, ' ');
					glm::vec3 newNormal(strtof((currentLine[1]).c_str(), 0), strtof(currentLine[2].c_str(), 0), strtof(currentLine[3].c_str(), 0));

					normals.push_back(newNormal);
				}
				else if (lineCStr[1] == ' ' || lineCStr[1] == '\t')
				{
					std::vector<std::string> currentLine = SplitString(line, ' ');
					glm::vec3 vertex(strtof((currentLine[1]).c_str(), 0), strtof(currentLine[2].c_str(), 0), strtof(currentLine[3].c_str(), 0));

					vertices.push_back(new Vertex((int)vertices.size(), vertex));
				}
			}
			else if (line.substr(0, 2) == "f ")
				break;
		}
		while ((!line.empty()) && (line.substr(0, 2) == "f "))
		{
			std::vector<std::string> currentLine = SplitString(line, ' ');
			std::vector<std::string> vertex1 = SplitString(currentLine[1], '/');
			std::vector<std::string> vertex2 = SplitString(currentLine[2], '/');
			std::vector<std::string> vertex3 = SplitString(currentLine[3], '/');
			processVertex(vertex1, vertices, indices);
			processVertex(vertex2, vertices, indices);
			processVertex(vertex3, vertices, indices);

			getline(file, line);
		}
		removeUnusedVertices(vertices);
		std::vector<float> verticesVectors;
		std::vector<float> texturesVectors;
		std::vector<float> normalsVectors;
		convertDataToVectors(vertices, textures, normals, verticesVectors, texturesVectors, normalsVectors);
		for (Vertex* vertex : vertices)
			delete vertex;

		Mesh* mesh = new Mesh();
		for (int i = 0; i < verticesVectors.size()/3; i ++)
		{
			mesh->Vertices.push_back(glm::vec3(verticesVectors[i * 3], verticesVectors[i * 3 + 1], verticesVectors[i * 3 + 2]));
			mesh->Normals.push_back(glm::vec3(normalsVectors[i * 3], normalsVectors[i * 3 + 1], normalsVectors[i * 3 + 2]));
			mesh->U.push_back(texturesVectors[i * 2]);
			mesh->V.push_back(texturesVectors[i * 2 + 1]);
		}
		mesh->Indices = indices;

		for (int i = 0; i < indices.size();)
		{
			SmoothUVMeshTriangle* triangle_ptr = new SmoothUVMeshTriangle(mesh, indices[i], indices[i + 1], indices[i + 2]);

			//FlatMeshTriangle* triangle_ptr = new FlatMeshTriangle(mesh, indices[i], indices[i+1], indices[i+2]);
			//triangle_ptr->ComputeNormal(false);
			triangle_ptr->SetMaterial(mat);
			grid->AddObject(triangle_ptr);
			//objects.push_back(triangle_ptr);

			i += 3;
		}

		grid->SetupCells();

		return new Instance(grid);
	}

	void World::build(Scene& scene, int nrOfSamples)
	{
		printf("building the world\n");
		Window* window = &Application::Get().GetWindow();
		Sampler* sampler = new MultiJittered(nrOfSamples);

		vp.set_hres(window->GetWidth());
		vp.set_vres(window->GetHeight());
		vp.sampler_ptr = sampler;
		vp.num_samples = nrOfSamples;
		vp.max_depth = 10;

		background_color = black;
		tracer_ptr = new Whitted(this);
		//tracer_ptr = new RayCast(this);

		RTAmbient* occluder_ptr = new RTAmbient;
		occluder_ptr->SetLs(1.0f);
		//occluder_ptr->SetSampler(vp.sampler_ptr);

		SetAmbientLight(occluder_ptr);

		Camera* cam = scene.GetGameCamera();

		RTPinhole* pinhole_ptr = new RTPinhole;
		glm::vec3 pos = cam->GetTransform()->Position;
		pinhole_ptr->SetEye(-pos);

		glm::vec3 rotation = cam->GetTransform()->Rotation;
		glm::vec3 direction;
		direction.x = cos(glm::radians(rotation.x)) * sin(glm::radians(rotation.y)); 
		direction.y = -sin(glm::radians(rotation.x));
		direction.z = -cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
		std::cout << direction.x << ", " << direction.y << ", " << direction.z << std::endl;

		pinhole_ptr->SetLookat(direction);
		pinhole_ptr->SetViewDistance(cam->GetNearPlane());
		pinhole_ptr->SetFOV(cam->GetFOV());
		//pinhole_ptr->SetZoom(1);
		pinhole_ptr->compute_uvw();
		SetCamera(pinhole_ptr);

		RTPointLight* light_ptr2 = new RTPointLight;
		light_ptr2->SetLocation(glm::vec3(0, 100, 100));
		//light_ptr2->SetColor(glm::vec3(1.0, 0, 0));
		light_ptr2->SetLs(3.0);
		AddLight(light_ptr2);

		//RTPointLight* light_ptr3 = new RTPointLight;
		//light_ptr3->SetLocation(glm::vec3(100, 100, -100));
		////light_ptr2->SetColor(glm::vec3(1.0, 0, 0));
		//light_ptr3->SetLs(3.0);
		//light_ptr3->EnableShadows(false);
		//AddLight(light_ptr3);

		RTMatte* matte_ptr1 = new RTMatte;
		matte_ptr1->SetKa(0.25);
		matte_ptr1->SetKd(1.0);
		ConstantColor* texture1 = new RTConstantColor;
		texture1->SetColor({ 0.1, 0.1, 0.5 });
		matte_ptr1->SetCd(texture1);	  				// yellow

		//RTPhong* phong = new RTPhong;
		//phong->SetKa(0.1);
		//phong->SetKd(0.75);
		//phong->SetKs(0.25);
		//phong->SetExp(50);
		//ConstantColor* texture2 = new RTConstantColor;
		//texture2->SetColor({ 0.75, 0.75, 0 });
		//phong->SetCd(texture2);

		RTPhong* phong2 = new RTPhong;
		phong2->SetKa(0.1);
		phong2->SetKd(0.75);
		phong2->SetKs(0.25);
		phong2->SetExp(75);
		ConstantColor* texture3 = new RTConstantColor;
		texture3->SetColor({ 0.90, 0.1, 0.1 });
		phong2->SetCd(texture3);

		//RTReflective* reflective = new RTReflective;
		//reflective->SetKa(0.25);
		//reflective->SetKd(0.5);
		//ConstantColor* texture4 = new RTConstantColor;
		//texture4->SetColor({ 0.75, 0.75, 0 });
		//reflective->SetCd(texture4);
		//reflective->SetKs(0.15);
		//reflective->SetExp(100);
		//reflective->SetKr(0.75);
		//ConstantColor* whiteTexture = new RTConstantColor;
		//whiteTexture->SetColor(white);
		//reflective->SetCr(whiteTexture);

		Image* imageptr = new Image("../Engine/res/textures/huis.png");


		RTImageTexture* imageTexture = new RTImageTexture;
		imageTexture->SetImage(imageptr);
		imageTexture->SetMapping(nullptr);

		RTMatte* matteTex = new RTMatte;
		matteTex->SetKa(0.45);
		matteTex->SetKd(0.65);
		matteTex->SetCd(imageTexture);

		//RTReflective* reflective2 = new RTReflective;
		//reflective2->SetKa(0.25);
		//reflective2->SetKd(0.5);
		//ConstantColor* texture5 = new RTConstantColor;
		//texture5->SetColor({ 0.75, 0.1, 0.1 });
		//reflective2->SetCd(imageTexture);
		//reflective2->SetKs(0.15);
		//reflective2->SetExp(100);
		//reflective2->SetKr(0.75);
		//reflective2->SetCr(whiteTexture);

		
		
		/*Instance* sphereInstance = CreateMesh("../Engine/res/models/sphere.obj", phong2);
		sphereInstance->SetMaterial(matteTex);
		sphereInstance->SetTransform({ 2,2,-10 }, {0,0,0}, {1,1,1});
		add_object(sphereInstance);*/

		for (auto obj : scene.GameObjects())
		{
			if (obj->GetComponent<MeshRenderer>())
			{
				std::cout << obj->GetComponent<MeshRenderer>()->GetRawModel()->path.c_str() << std::endl;
				RTPhong* phong = new RTPhong;
				auto* mat = (OpenGLPhong*)obj->GetComponent<MeshRenderer>()->GetMaterial();
				phong->SetKa(mat->GetKa());
				phong->SetCd(imageTexture);
				phong->SetKd(mat->GetKd());
				phong->SetKs(mat->GetKs());
				phong->SetExp(mat->GetExp());
				Texture* texture3 = mat->GetCd();
				phong->SetCd(texture3);
				Instance* instance = CreateMesh(obj->GetComponent<MeshRenderer>()->GetRawModel()->path, phong);
				Transform* transform = obj->GetComponent<Transform>();
				instance->SetTransform(transform->Position, transform->Rotation, transform->Scale);
				
				add_object(instance);
			}
			
		}
		if (image)
		{
			delete image;
		}
		image = new Image(vp.vres,vp.hres);
	}

	ShadeRec World::hit_objects(const Ray& ray)
	{
		ShadeRec sr(this);
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