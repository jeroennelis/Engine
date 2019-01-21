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
	}

	void GameObject::OnUpdate()
	{
		for (std::shared_ptr<Component> component : m_Components)
			component->Update();

		for (std::shared_ptr<GameObject> child : m_Children)
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

			for (std::shared_ptr<GameObject> child : m_Children)
			{
				child->OnHierarchyRender(currentGameObject);
			}
			ImGui::TreePop();
		}
	}

	void GameObject::OnInspectorRender()
	{

	}

	void GameObject::AddChild(std::shared_ptr<GameObject> go)
	{
		m_Children.push_back(go);
	}

	void GameObject::AddComponent(std::shared_ptr<Component> newComp)
	{
		for (std::shared_ptr<Component> comp : m_Components)
		{
			if (newComp->Type()== comp->Type())
			{
				EN_CORE_INFO("this Game Object already contains a {0}", newComp->Name());
				return;
			}
		}
		EN_CORE_INFO("Added a {0}", newComp->Name());
		m_Components.push_back(newComp);
	}
}