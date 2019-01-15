#pragma once

#include "Engine/Components/Component.h"


namespace Engine {
	class GameObject
	{
	public:
		GameObject(const std::string& name);
		~GameObject();

		void OnUpdate();
		void OnHierarchyRender(GameObject* currentGameObject);
		void OnInspectorRender();

		void AddChild(GameObject* go);
		void AddComponent(Component* comp);

		inline const std::string& Name() const { return m_Name; }

		template <class component_type>
		component_type* GetComponent()
		{
			for (auto* comp : m_Components)
				if (component_type::ComponentType == comp->ID())
					return dynamic_cast<component_type*>(comp);
			return NULL;
		}

	private:
		std::string					m_Name;
		std::vector<GameObject*>	m_Children;
		std::vector<Component*>		m_Components;
	};
}


