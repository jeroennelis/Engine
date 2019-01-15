#include "enpch.h"
#include "Scene.h"

namespace Engine {

	Scene* Scene::m_Current = nullptr;

	Scene::Scene()
		:m_Name("New Scene")
	{
		if (!m_Current)
			m_Current = this;
	}

	Scene::Scene(const std::string & name = "New Scene")
		:m_Name(name)
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
		EN_CORE_INFO("update {0}", m_Name);
		for (auto go : m_GameObjects)
			go->OnUpdate();
	}
}