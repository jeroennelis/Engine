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

	void GameObject::OnHierarchyRender(GameObject* currentGameObject, int& node_clicked, unsigned int& index, int& selection_mask)
	{
		if (!m_Children.size())
		{	
			ImGui::Indent();
			if (ImGui::Selectable(m_Name.c_str(), (selection_mask & (1 << index))))
			{
				node_clicked = index;
				Scene::SetSelectedGameObject(this);
			}
			ContextMenu(node_clicked,index);
			

			index++;
			ImGui::Unindent();
		}
		else
		{
			ImGuiTreeNodeFlags node_flags = ((selection_mask & (1 << index)) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
			bool opened = ImGui::TreeNodeEx((void*)(intptr_t)index, node_flags, m_Name.c_str(), index);
			static bool edit = false;
			if (ImGui::IsItemClicked(0))
			{
				EN_CORE_INFO("{0}", index);
				node_clicked = index;
				Scene::SetSelectedGameObject(this);
				if (ImGui::IsMouseDoubleClicked(0))
				{
					EN_CORE_INFO("test");
					edit = true;
				}
			}
			ContextMenu(node_clicked, index);

			if (opened)
			{
				index++;
				for (int i = 0; i < m_Children.size(); i++)
				{
					m_Children[i]->OnHierarchyRender(Scene::SelectedGameObject(), node_clicked, index, selection_mask);
				}
				ImGui::TreePop();
			}
			else
			{
				GetNrOfChildrenRecursively(index);
			}
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
	void GameObject::GetNrOfChildrenRecursively(unsigned int& nrSoFar)
	{
		if (!m_Children.size())
		{
			nrSoFar++;
			return;
		}
		
		for (std::shared_ptr<GameObject>& child : m_Children)
		{
			child->GetNrOfChildrenRecursively(nrSoFar);
		}
		nrSoFar++;
	}

	void GameObject::ContextMenu(int& node_clicked, unsigned int& index)
	{
		if (ImGui::BeginPopupContextItem())
		{
			Scene::SetSelectedGameObject(this);
			node_clicked = index;
			if (ImGui::MenuItem("Copy", "", false, false))
			{

			}
			if (ImGui::MenuItem("Paste", "", false, false))
			{

			}
			ImGui::Separator();
			if (ImGui::MenuItem("Rename", "", false, false))
			{

			}
			if (ImGui::MenuItem("Ducplicate", "", false, false))
			{

			}
			if (ImGui::MenuItem("Delete", "", false, false))
			{

			}
			ImGui::Separator();
			ImGui::Separator();

			if (ImGui::MenuItem("Create Empty", "", false, true))
			{
				AddChild(std::make_shared<GameObject>(GameObject("GameObject")));
			}
			if (ImGui::BeginMenu("3D Object"))
			{
				if (ImGui::MenuItem("Cube", "", false, false))
				{

				}
				if (ImGui::MenuItem("Sphere", "", false, false))
				{

				}
				ImGui::EndMenu();
			}
			ImGui::EndPopup();
		}
	}
}