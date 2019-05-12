#include  "enpch.h"
#include  "GameObject.h" 

#include  "ImGui/ImGuiLayer.h" 
#include  "imgui.h"
#include  "Engine/Logic/Scene.h"
#include "Components/Transform.h"
#include "Platform/OpenGl/MeshRenderer.h"
#include "Platform/OpenGl/Loader.h"

namespace Engine {
	GameObject::GameObject(const std::string & name, GameObject* parent)
		:m_Name(name), m_Index(Scene::ObjectCount++), m_Parent(parent)
	{
		if (parent)
			m_Components.push_back(std::make_shared<Transform>(parent->GetComponent<Transform>()));
		else
			m_Components.push_back(std::make_shared<Transform>());
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
			std::stringstream name;
			name << m_Name << "##" << index;
			if (ImGui::Selectable(name.str().c_str(), (selection_mask & (1 << index))))
			{
				node_clicked = index;
				Scene::SetSelectedGameObject(this);
			}
			ContextMenu(node_clicked,index);
			if (ImGui::BeginDragDropTarget())
			{
				MeshRenderer* renderer = GetComponent<MeshRenderer>();
				if (renderer)
				{
					if (const ImGuiPayload* pl = ImGui::AcceptDragDropPayload("Material"))
					{

						{
							renderer->SetMaterial(Loader::Get()->DraggedMaterial());
							Loader::Get()->SetDraggedMaterial(nullptr);
						}

					}
				}
				
				ImGui::EndDragDropTarget();
			}

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
				node_clicked = index;
				Scene::SetSelectedGameObject(this);
				if (ImGui::IsMouseDoubleClicked(0))
				{
					edit = true;
				}
			}
			if (ImGui::BeginDragDropTarget())
			{
				MeshRenderer* renderer = GetComponent<MeshRenderer>();
				if (renderer)
				{
					if (const ImGuiPayload* pl = ImGui::AcceptDragDropPayload("Material"))
					{

						{
							renderer->SetMaterial(Loader::Get()->DraggedMaterial());
							Loader::Get()->SetDraggedMaterial(nullptr);
						}

					}
				}

				ImGui::EndDragDropTarget();
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

	void GameObject::Render()
	{
		MeshRenderer* renderer = GetComponent<MeshRenderer>();
		if (renderer)
		{
			renderer->Draw();
		}
		for (auto child : m_Children)
		{
			child->Render();
		}
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
				EN_CORE_INFO( "this Game Object already contains a {0}" , newComp->Name());
				return;
			}
		}
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
			if (ImGui::MenuItem( "Copy" , ""  , false, false))
			{

			}
			if (ImGui::MenuItem( "Paste" , ""  , false, false))
			{

			}
			ImGui::Separator();
			if (ImGui::MenuItem( "Rename" , "" , false, true))
			{
				renaming = true;
				
			}
			/*if (ImGui::MenuItem( "Ducplicate" , ""  , false, false))
			{

			}*/
			if (ImGui::MenuItem( "Delete" , "" , false, true))
			{
				for (std::vector<std::shared_ptr<GameObject>>::iterator it = Scene::Current()->GameObjects().begin(); it != Scene::Current()->GameObjects().end(); ++it)
				{
					GameObject* temp = it->get();
					if(temp->Index() == m_Index)
					{ 
						Scene::Current()->GameObjects().erase(it);

						// temp
						ImGui::EndPopup();
						
						return;
					}
				}
			}
			ImGui::Separator();
			ImGui::Separator();

			if (ImGui::MenuItem( "Create Empty" , "" , false, true))
			{
				AddChild(std::make_shared<GameObject>(GameObject( "GameObject" , this)));
			}
			if (ImGui::BeginMenu( "3D Object" ))
			{
				if (ImGui::MenuItem( "Cube" , ""  , false, true))
				{
					AddChild(Scene::CreateCube(this));
				}
				if (ImGui::MenuItem( "Sphere" , ""  , false, true))
				{
					AddChild(Scene::CreateSphere(this));
				}
				if (ImGui::MenuItem("target", "", false, true))
				{
					AddChild(Scene::CreateTarget(this));
				}
				ImGui::EndMenu();
			}
			ImGui::EndPopup();
		}

		//rename
		if (renaming)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 2.0f);
			
			static bool configured;
			if (!configured)
			{
				ImGui::SetKeyboardFocusHere(0);
				configured = true;
			}
			
			
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 20);
			ImGui::SetCursorPosX(0);
			ImGui::PushItemWidth(ImGui::GetWindowWidth());
			static char buf[32];
			strcpy(buf, m_Name.c_str());
			if (!ImGui::IsItemHovered() && ImGui::IsMouseClicked(0)) {
				renaming = false;
				configured = false;
			}
			
			if (ImGui::InputText( "##text" , buf, IM_ARRAYSIZE(buf), ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll))
			{

				m_Name = buf;
				renaming = false;
				configured = false;
			}
			ImGui::PopStyleVar();
			ImGui::PopItemWidth();
		}
	}
}