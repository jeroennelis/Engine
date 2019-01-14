#include "enpch.h"
#include "GameObject.h"


namespace Engine {
	GameObject::GameObject(const std::string & name)
		:m_Name(name)
	{
	}

	GameObject::~GameObject()
	{
		for (GameObject* child : m_Children)
			delete child;
	}

	void GameObject::Update()
	{
		for (Component* component : m_Components)
			component->Update();

		for (GameObject* child : m_Children)
			child->Update();
	}

	void GameObject::AddChild(GameObject * go)
	{
		m_Children.push_back(go);
	}

	void GameObject::AddComponent(Component * comp)
	{
		m_Components.push_back(comp);
	}
}