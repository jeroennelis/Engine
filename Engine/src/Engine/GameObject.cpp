#include "enpch.h"
#include "GameObject.h"

#include "ImGui/ImGuiLayer.h"
#include "imgui.h";
#include "Engine/Logic/Scene.h"

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

	void GameObject::OnUpdate()
	{
		for (Component* component : m_Components)
			component->Update();

		for (GameObject* child : m_Children)
			child->OnUpdate();
	}

	void GameObject::OnHierarchyRender(GameObject* currentGameObject)
	{
		if (ImGui::TreeNode(m_Name.c_str()))
		{
			char label[] = "this";
			ImGui::Bullet(); ImGui::Selectable(label, false);
			if ((ImGui::IsItemHovered() || ImGui::IsItemFocused()) && ImGui::IsMouseClicked(0))
				Scene::SetSelectedGameObject(this);
			
			for (GameObject* child : m_Children)
			{
				child->OnHierarchyRender(currentGameObject);
			}
			ImGui::TreePop();
		}
	}

	void GameObject::OnInspectorRender()
	{

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