#include  "enpch.h" 
#include  "Scene.h" 
#include  "Platform/OpenGl/MeshRenderer.h"
#include "Platform/OpenGl/OBJLoader.h"
#include "Engine/Components/Camera.h"
#include "Platform/OpenGl/Loader.h"
#include "Engine/Application.h"


namespace Engine {

	Scene* Scene::m_Current = nullptr;
	GameObject* Scene::m_SelectedGameObject = nullptr;
	Material* Scene::m_SelectedMaterial = nullptr;
	unsigned int Scene::ObjectCount = 0;
	Camera* Scene::m_GameCamera = nullptr;
	Camera* Scene::m_SceneCamera = nullptr;

	Scene::Scene()
		:m_Name("New Scene"), gravity(glm::vec3(0.0, -9.81f, 0)), particleWorld(1000000000), runPhysics(false)
	{
		if (!m_Current)
			m_Current = this;
		std::shared_ptr<GameObject> camera = std::make_shared<GameObject>("Camera");
		std::shared_ptr<Camera> cam_comp = std::make_shared<Camera>(camera->GetComponent<Transform>());
		camera->AddComponent(cam_comp);
		AddGameObject(camera);
		SetGameCamera(cam_comp.get());
		camera->GetComponent<Transform>()->Position = glm::vec3(0,10,-10.0f);
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
		Material* mat = Loader::Get()->GetMaterials().at(3);
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
		Material* mat = Loader::Get()->GetMaterials().at(3);
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
		Material* mat = Loader::Get()->GetMaterials().at(3);
		Shader*  BasicShader = Loader::Get()->GetShader("basic");
		std::shared_ptr<GameObject> sphere = std::make_shared<GameObject>("sphere", parent);
		Transform* transform = sphere->GetComponent<Transform>();
		std::shared_ptr<MeshRenderer> meshRenderer = std::make_shared<MeshRenderer>(mat, rawModel, transform); //TODO: mem leak
		sphere->AddComponent(meshRenderer);
		return sphere;
	}

	void Scene::DeleteGameObject(const std::shared_ptr<GameObject>& object)
	{
		/*for (auto it = m_GameObjects.begin(); it!= m_GameObjects.end() ; it++)
		{
			if(*it == object)
				EN_CORE_INFO("deleting {0}", object->Name());
		}*/
	}

	void Scene::AddCube(const glm::vec3& position)
	{
		RawModel* rawModel = Loader::Get()->GetModel("target");
		Material* mat = Loader::Get()->GetMaterials().at(3);
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
		Material* mat = Loader::Get()->GetMaterials().at(4);

		GameObject sphere = GameObject("killhouse");
		Transform* transform = sphere.GetComponent<Transform>();
		std::shared_ptr<MeshRenderer> meshRenderer = std::make_shared<MeshRenderer>(mat, rawModel, transform);  //TODO: mem leak
		sphere.AddComponent(meshRenderer);
		Current()->AddGameObject(std::make_shared<GameObject>(sphere));
	}
}