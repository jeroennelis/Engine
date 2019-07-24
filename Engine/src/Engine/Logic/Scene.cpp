#include  "enpch.h" 
#include  "Scene.h" 
#include  "Platform/OpenGl/MeshRenderer.h"
#include "Platform/OpenGl/OBJLoader.h"
#include "Engine/Components/Camera.h"
#include "Platform/OpenGl/Loader.h"
#include "Engine/Application.h"
#include "Platform/OpenGl/PointCloudRenderer.h"
#include "Platform/OpenGl/ConeRenderer.h"

#include "Platform/OpenGl/RawModel.h"
#include "Platform/OpenGl/Materials/OpenGLPhong.h"
#include "Platform/OpenGl/Materials/OpenGLCone.h"

namespace Engine {

	Scene* Scene::m_Current = nullptr;
	GameObject* Scene::m_SelectedGameObject = nullptr;
	OpenGLMaterial* Scene::m_SelectedMaterial = nullptr;
	unsigned int Scene::ObjectCount = 0;
	Camera* Scene::m_GameCamera = nullptr;
	Camera* Scene::m_SceneCamera = nullptr;

	Scene::Scene()
		:m_Name("New Scene"), gravity(glm::vec3(0.0, -9.81f, 0)), particleWorld(1), runPhysics(false)
	{
		if (!m_Current)
			m_Current = this;
		std::shared_ptr<GameObject> camera = std::make_shared<GameObject>("Camera");
		std::shared_ptr<Camera> cam_comp = std::make_shared<Camera>(camera->GetComponent<Transform>());
		camera->AddComponent(cam_comp);
		AddGameObject(camera);
		SetGameCamera(cam_comp.get());
		camera->GetComponent<Transform>()->Position = glm::vec3(0, 0, 0);
		camera->GetComponent<Transform>()->Rotation = glm::vec3(0, 0, 0);
		m_SceneCamera = cam_comp.get();

		
	}

	Scene::Scene(const std::string & name = "New Scene")
		:m_Name(name), gravity(glm::vec3(0.0, 9.81f, 0)), particleWorld(1)
	{
		if (!m_Current)
			m_Current = this;
	}

	Scene::~Scene()
	{
	}

	void Scene::AddGameObject(std::shared_ptr<GameObject> go)
	{
		m_GameObjects.push_back(go);
	}

	GameObject* Scene::AddRawModel(RawModel * model)
	{
		OpenGLMaterial* mat = Loader::Get()->GetMaterials().at(4);

		std::shared_ptr<GameObject> go = std::make_shared<GameObject>("model");		//TODO
		Transform* transform = go->GetComponent<Transform>();
		std::shared_ptr<MeshRenderer> meshRenderer = std::make_shared<MeshRenderer>(mat, model, transform);  //TODO: mem leak
		go->AddComponent(meshRenderer);
		Current()->AddGameObject(go);
		return go.get();
	}

	void Scene::OnUpdate()
	{
		for (auto go : m_GameObjects)
			go->OnUpdate();
	}

	void Scene::Render()
	{
		for (auto& go : m_GameObjects)
		{
			go->Render();
		}
	}

	std::shared_ptr<GameObject> Scene::CreateCube(GameObject* parent)
	{
		RawModel* rawModel = Loader::Get()->GetModel("cube");
		OpenGLMaterial* mat = Loader::Get()->GetMaterials().at(3);
		std::shared_ptr<GameObject> cube = std::make_shared<GameObject>("cube", parent);
		Transform* parentTransform = parent->GetComponent<Transform>();
		Transform* transform = cube->GetComponent<Transform>();
		std::shared_ptr<MeshRenderer> meshRenderer = std::make_shared<MeshRenderer>(mat, rawModel, transform);  //TODO: mem leak
		cube->AddComponent(meshRenderer);
		return cube;
	}

	std::shared_ptr<GameObject> Scene::CreateTarget(GameObject* parent)
	{
		RawModel* rawModel = Loader::Get()->GetModel("target");
		OpenGLMaterial* mat = Loader::Get()->GetMaterials().at(3);
		Shader* BasicShader = Loader::Get()->GetShader("basic");
		std::shared_ptr<GameObject> cube = std::make_shared<GameObject>("target", parent);
		Transform* parentTransform = parent->GetComponent<Transform>();
		Transform* transform = cube->GetComponent<Transform>();
		std::shared_ptr<MeshRenderer> meshRenderer = std::make_shared<MeshRenderer>(mat, rawModel, transform);  //TODO: mem leak
		cube->AddComponent(meshRenderer);
		return cube;
	}

	std::shared_ptr<GameObject> Scene::CreateSphere(GameObject* parent)
	{
		RawModel* rawModel = Loader::Get()->GetModel("sphere");
		OpenGLMaterial* mat = Loader::Get()->GetMaterials().at(3);
		Shader*  BasicShader = Loader::Get()->GetShader("basic");
		std::shared_ptr<GameObject> sphere = std::make_shared<GameObject>("sphere", parent);
		Transform* transform = sphere->GetComponent<Transform>();
		std::shared_ptr<MeshRenderer> meshRenderer = std::make_shared<MeshRenderer>(mat, rawModel, transform); //TODO: mem leak
		sphere->AddComponent(meshRenderer);
		return sphere;
	}

	void Scene::DeleteGameObject(const std::shared_ptr<GameObject>& object)
	{
		for (auto it = m_GameObjects.begin(); it!= m_GameObjects.end() ; it++)
		{
			if(*it == object)
				EN_CORE_INFO("deleting {0}", object->Name());
		}
	}

	void Scene::AddCube(const glm::vec3& position)
	{
		RawModel* rawModel = Loader::Get()->GetModel("target");
		OpenGLMaterial* mat = Loader::Get()->GetMaterials().at(3);
		GameObject cube = GameObject("target");
		Transform* transform = cube.GetComponent<Transform>();
		transform->Position = position;
		std::shared_ptr<MeshRenderer> meshRenderer = std::make_shared<MeshRenderer>(mat, rawModel, transform);  //TODO: mem leak
		cube.AddComponent(meshRenderer);
		Current()->AddGameObject(std::make_shared<GameObject>(cube));
	}

	void Scene::AddSphere()
	{
		RawModel* rawModel = Loader::Get()->GetModel("killhouse");
		OpenGLMaterial* mat = Loader::Get()->GetMaterials().at(4);

		GameObject sphere = GameObject("killhouse");
		Transform* transform = sphere.GetComponent<Transform>();
		std::shared_ptr<MeshRenderer> meshRenderer = std::make_shared<MeshRenderer>(mat, rawModel, transform);  //TODO: mem leak
		sphere.AddComponent(meshRenderer);
		Current()->AddGameObject(std::make_shared<GameObject>(sphere));
	}

	void Scene::AddPointCloud()
	{
		GameObject pointcloud("pelt");
		Transform* transform = pointcloud.GetComponent<Transform>();
		std::vector<RawModel> pcm = Loader::Get()->GetPointCloud();
		OpenGLPhong* mat = new OpenGLPhong(Loader::Get()->GetShader("pointcloud"), "pointcloud");
		transform->Position = glm::vec3(0.4, 35.2, -0.4);
		transform->Rotation = glm::vec3(-90, 0, 0);


		std::shared_ptr<PointCloudRenderer> pcr = std::make_shared<PointCloudRenderer>(mat, pcm, transform);
		pointcloud.AddComponent(pcr);

		Current()->AddGameObject(std::make_shared<GameObject>(pointcloud));
	}

	void Scene::AddCone()
	{
		GameObject coneOBJ("cone");
		Transform* transform = coneOBJ.GetComponent<Transform>();
		RawModel cone = Loader::Get()->GetCone();
		OpenGLMaterial* mat = new OpenGLCone(Loader::Get()->GetShader("cone"), "cone");

		std::shared_ptr<ConeRenderer> pcr = std::make_shared<ConeRenderer>(mat, cone, transform);
		coneOBJ.AddComponent(pcr);

		Current()->AddGameObject(std::make_shared<GameObject>(coneOBJ));
	}
}