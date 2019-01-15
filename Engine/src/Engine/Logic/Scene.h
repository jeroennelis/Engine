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
				
		inline const std::string& Name() const { return m_Name; }

		void AddGameObject(std::shared_ptr<GameObject> go);

		void OnUpdate();


	private:
		static Scene* m_Current;
		std::string m_Name;

		std::vector<std::shared_ptr<GameObject>> m_GameObjects;
	};

}


