#include "enpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"

#include "Platform/OpenGl/ImGuiOpenGLRenderer.h"
// TEMP
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Engine/GameObject.h"

#include "Engine/Application.h"

#include "Engine/Logic/Scene.h"


#include "imgui_internal.h"

namespace Engine {

	bool ImGuiLayer::m_ShowStatistics = true;

	ImGuiLayer::ImGuiLayer()
		:Layer("ImGui Layer")
	{
	}
	ImGuiLayer::~ImGuiLayer()
	{
	}
	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

ImGui_ImplOpenGL3_Init("#version 410");

EN_CORE_INFO("attached imGui layer");
	}
	void ImGuiLayer::OnDetach()
	{
	}
	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_time > 0.0 ? (time - m_time) : (1.0f / 60.0f);
		m_time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		RenderMenuBar();
		RenderHierarchyWindow();
		RenderGameWindow();
		RenderInspectorWindow();
		RenderConsoleWindow();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event & event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseButtonPressedEvent>(EN_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(EN_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(EN_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(EN_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<KeyPressedEvent>(EN_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(EN_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(EN_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(EN_BIND_EVENT_FN(ImGuiLayer::OnwindowResizeEvent));
	}

	void ImGuiLayer::RenderMenuBar()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New Scene", "CTRL+N", false, false)) {}
				if (ImGui::MenuItem("Open Scne", "CTRL+O", false, false)) {}
				ImGui::Separator();
				if (ImGui::MenuItem("Save", "CTRL+S", false, false)) {}
				if (ImGui::MenuItem("Save As...", "CTRL+SHIFT+N", false, false)) {}
				ImGui::Separator();
				if (ImGui::MenuItem("New Project", "", false, false)) {}
				if (ImGui::MenuItem("Open Project", "", false, false)) {}
				if (ImGui::MenuItem("Save Project", "", false, false)) {}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("Undo", "CTRL+Z", false, false)) {}
				if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
				ImGui::Separator();
				if (ImGui::MenuItem("Cut", "CTRL+X", false, false)) {}
				if (ImGui::MenuItem("Copy", "CTRL+C", false, false)) {}
				if (ImGui::MenuItem("Paste", "CTRL+V", false, false)) {}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Assets"))
			{
				if (ImGui::MenuItem("Undo", "CTRL+Z", false, false)) {}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("GameObject"))
			{
				if (ImGui::MenuItem("Create Empty", "CTRL+SHIFT+N")) { AddEmptyGameObject(); }
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Component"))
			{
				bool enabled = false;
				if (Scene::Current()->SelectedGameObject())
					enabled = true;

				if (ImGui::BeginMenu("Test"))
				{
					if (ImGui::MenuItem("Test Component", "", false, enabled)) 
					{
						Component* comp = new TestComponent;
						Scene::Current()->SelectedGameObject()->AddComponent(comp);
					}
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Window"))
			{
				if (m_ShowStatistics)
				{
					if (ImGui::MenuItem("disable Statistics")) { ToggleStatistics(); }
					ImGui::EndMenu();
				}
				else
				{
					if (ImGui::MenuItem("enable Statistics")) { ToggleStatistics(); }
					ImGui::EndMenu();
				}
				
			}

			ImGui::EndMainMenuBar();
		}
	}

	void ImGuiLayer::RenderInspectorWindow()
	{
		ImGui::Begin("Inspector");
		
		if (Scene::SelectedGameObject())
		{
			for (Component * component : Scene::SelectedGameObject()->Components())
			{
				component->RenderInspectorInfo();
			}
		}
		ImGui::End();
	}

	void ImGuiLayer::RenderGameWindow()
	{

		ImGui::Begin("Game");

		//ShowHelpMarker("Click to select, CTRL+Click to toggle, double-click to open");
		static int selection_mask = 0x02;   // Dumb representation of what may be user-side selection state. You may carry selection state inside or outside your objects in whatever format you see fit.

		int node_clicked = -1;
		for (int i = 0; i < 5; i++)
		{
			ImGuiTreeNodeFlags node_flags = ((selection_mask & (1 << i)) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnDoubleClick;
			bool opened = ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "Selectable Child %d", i);
			if (ImGui::IsItemClicked())
				node_clicked = i;
			if (opened)
			{
				ImGui::Text("blah blah");
				ImGui::TreePop();
			}
		}
		if (node_clicked != -1)
		{
			// Update selection state. Process outside of tree loop to avoid visual inconsistencies during the clicking-frame.
			if (ImGui::GetIO().KeyCtrl)
				selection_mask ^= (1 << node_clicked);  // CTRL+click to toggle
			else
			{
				selection_mask = (1 << node_clicked);   // Click to single-select
			}

		}

		

		if (m_ShowStatistics)
		{
			const float DISTANCE = 10.0f;
			static int corner = 0;
			ImVec2 window_pos = ImVec2((corner & 1) ? ImGui::GetIO().DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? ImGui::GetIO().DisplaySize.y - DISTANCE : DISTANCE);
			ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
			if (corner != -1)
				ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
			ImGui::SetNextWindowBgAlpha(0.3f); // Transparent background
			ImVec2 pos(ImGui::GetWindowPos());
			ImVec2 size(ImGui::GetWindowSize());
			ImGui::SetNextWindowPos(ImVec2(pos.x + size.x - 210, pos.y + 20));
			ImGui::BeginChild("test", ImVec2(200, 100), m_ShowStatistics, (corner != -1 ? ImGuiWindowFlags_NoMove : 0) | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav);
			//ImGui::Begin("Game", &open, (corner != -1 ? ImGuiWindowFlags_NoMove : 0) | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav);

			ImGui::Text("Frame rate: %0.1f fps", ImGui::GetIO().Framerate);
			ImGui::Indent(84);
			ImGui::Text("%.3f ms/frame", 1000.0f / ImGui::GetIO().Framerate);
			ImGui::EndChild();
		}
		ImGui::End();
	}

	void ImGuiLayer::RenderHierarchyWindow()
	{
		ImGui::Begin("Hierarchy");

		for (auto gameObject : Scene::Current()->GameObjects())
			gameObject->OnHierarchyRender(Scene::SelectedGameObject());

		ImGui::BeginChild("test");
		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::Selectable("add new gameobject"))
			{
				AddEmptyGameObject();
			}
			if (ImGui::Selectable("testing"))
			{

			}
			ImGui::EndPopup();
		}
		ImGui::EndChild();

		ImGui::End();

		
	}

	void ImGuiLayer::RenderConsoleWindow()
	{
		ImGui::Begin("Console");
		ImGui::BulletText("Drag and drop to re-order");
		ImGui::Indent();
		static const char* names[6] = { "1. Adbul", "2. Alfonso", "3. Aline", "4. Amelie", "5. Anna", "6. Arthur" };
		int move_from = -1, move_to = -1;

		for (int n = 0; n < IM_ARRAYSIZE(names); n++)
		{
			if (ImGui::TreeNode(names[n]))
			{
				char label[] = "this";
				ImGui::Bullet();
				ImGui::Selectable(label, false);
				ImGui::TreePop();
			}
				
			ImGuiDragDropFlags src_flags = 0;
			src_flags |= ImGuiDragDropFlags_SourceNoDisableHover;     // Keep the source displayed as hovered
			src_flags |= ImGuiDragDropFlags_SourceNoHoldToOpenOthers; // Because our dragging is local, we disable the feature of opening foreign treenodes/tabs while dragging
			src_flags |= ImGuiDragDropFlags_SourceNoPreviewTooltip; // Hide the tooltip
			if (ImGui::BeginDragDropSource(src_flags))
			{
				if (!(src_flags & ImGuiDragDropFlags_SourceNoPreviewTooltip))
					ImGui::Text("Moving \"%s\"", names[n]);
				ImGui::SetDragDropPayload("DND_DEMO_NAME", &n, sizeof(int));
				ImGui::EndDragDropSource();
			}
			
				

			if (ImGui::BeginDragDropTarget())
			{
				ImGuiDragDropFlags target_flags = 0;
				target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;    // Don't wait until the delivery (release mouse button on a target) to do something
				target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect; // Don't display the yellow rectangle
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_NAME", target_flags))
				{
					move_from = *(const int*)payload->Data;
					move_to = n;
				}
				ImGui::EndDragDropTarget();
			}
				
		}
		

		if (move_from != -1 && move_to != -1)
		{
			// Reorder items
			int copy_dst = (move_from < move_to) ? move_from : move_to + 1;
			int copy_src = (move_from < move_to) ? move_from + 1 : move_to;
			int copy_count = (move_from < move_to) ? move_to - move_from : move_from - move_to;
			const char* tmp = names[move_from];
			//printf("[%05d] move %d->%d (copy %d..%d to %d..%d)\n", ImGui::GetFrameCount(), move_from, move_to, copy_src, copy_src + copy_count - 1, copy_dst, copy_dst + copy_count - 1);
			memmove(&names[copy_dst], &names[copy_src], (size_t)copy_count * sizeof(const char*));
			names[move_to] = tmp;
			ImGui::SetDragDropPayload("DND_DEMO_NAME", &move_to, sizeof(int)); // Update payload immediately so on the next frame if we move the mouse to an earlier item our index payload will be correct. This is odd and showcase how the DnD api isn't best presented in this example.
		}
		ImGui::Unindent();


		ImGui::End();
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent & e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		//let other layers be able to process event
		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent & e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;

		//let other layers be able to process event
		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent & e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());

		//let other layers be able to process event
		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent & e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel += e.GetYOffset(); 
		io.MouseWheelH += e.GetXOffset();

		//let other layers be able to process event
		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent & e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

		//let other layers be able to process event
		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent & e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;
		
		
		//let other layers be able to process event
		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent & e)
	{
		ImGuiIO& io = ImGui::GetIO();
		int keycode = e.GetKeyCode();
		if (keycode > 0 && keycode < 0x10000)
			io.AddInputCharacter((unsigned short)keycode);

		//let other layers be able to process event
		return false;
	}

	bool ImGuiLayer::OnwindowResizeEvent(WindowResizeEvent & e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight());

		//let other layers be able to process event
		return false;
	}

	void ImGuiLayer::ToggleStatistics()
	{
		m_ShowStatistics = !m_ShowStatistics;
	}

	void ImGuiLayer::AddEmptyGameObject()
	{
		EN_CORE_INFO("add new gameObject");
		GameObject newObject = GameObject("new gameobject");
		Scene::Current()->AddGameObject(std::make_shared<GameObject>(newObject));
	}
}
