#pragma once

#include  "Engine/Components/Component.h" 
#include "glm/glm.hpp"


namespace Engine {
	class GameObject
	{
	public:
		GameObject(const std::string& name, GameObject* parent = nullptr);
		~GameObject();

		inline bool operator==(const GameObject& rhs) { return m_Index = rhs.Index(); }

		void OnUpdate();
		void OnHierarchyRender(GameObject* currentGameObject, int& node_clicked, unsigned int& index, int& selection_mask);
		void OnInspectorRender();

		void Render();

		void AddChild(std::shared_ptr<GameObject> go);
		void AddComponent(std::shared_ptr<Component> comp);

		inline const std::string& Name() const { return m_Name; }
		inline const unsigned int Index() const { return m_Index; }
		inline const std::vector<std::shared_ptr<Component>>& Components()const { return m_Components; }
		inline const std::vector<std::shared_ptr<GameObject>>& Children()const { return m_Children; }
		inline const glm::mat4& TransformMatrix() { return m_TransformMatrix; }

		template <class component_type>
		component_type* GetComponent()
		{
			for (std::shared_ptr<Component> comp : m_Components)
				if (component_type::ComponentType == comp->ID())
					return dynamic_cast<component_type*>(comp.get());
			return NULL;
		}

	private:
		std::string									m_Name;
		std::vector<std::shared_ptr<GameObject>>	m_Children;
		std::vector<std::shared_ptr<Component>>		m_Components;

		GameObject* m_Parent;

		glm::mat4 m_TransformMatrix;
		
		//TODO automate
		void GetNrOfChildrenRecursively(unsigned int& nrSoFar);
		void GameObject::ContextMenu(int& node_clicked, unsigned int& index);

		bool renaming;
		unsigned int m_Index;
	};
}


