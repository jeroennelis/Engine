#pragma once
#include "Engine/GameObject.h"

namespace Engine {

	class Scene
	{
	public:
		Scene();
		Scene(const std::string& name);
		~Scene();

		inline static Scene* Current() { return m_Current; }
		inline static void SetCurrent(Scene* scene) { m_Current = scene; }

		inline static GameObject* SelectedGameObject() { return m_SelectedGameObject; }
		inline static void SetSelectedGameObject(GameObject* gameObject) { m_SelectedGameObject = gameObject; }
				
		inline const std::string& Name() const { return m_Name; }

		inline const std::vector<std::shared_ptr<GameObject>>& GameObjects()const { return m_GameObjects; }

		void AddGameObject(std::shared_ptr<GameObject> go);

		void OnUpdate();


	private:
		static Scene* m_Current;
		static GameObject* m_SelectedGameObject;
		std::string m_Name;

		std::vector<std::shared_ptr<GameObject>> m_GameObjects;
	};

}


