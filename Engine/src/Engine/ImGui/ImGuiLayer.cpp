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


		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		io.ConfigDockingWithShift = false;


		enum ImGuiDockNodeFlags_
		{
			ImGuiDockNodeFlags_None = 0,
			ImGuiDockNodeFlags_KeepAliveOnly = 1 << 0,   // Don't display the dockspace node but keep it alive. Windows docked into this dockspace node won't be undocked.
			ImGuiDockNodeFlags_NoSplit = 1 << 1,   // Disable splitting the node into smaller nodes. Useful e.g. when embedding dockspaces into a main root one (the root one may have splitting disabled to reduce confusion)
			ImGuiDockNodeFlags_NoDockingInCentralNode = 1 << 4,   // Disable docking inside the Central Node, which will be always kept empty.
			ImGuiDockNodeFlags_PassthruInEmptyNodes = 1 << 5,   // When Central Node is empty: let inputs pass-through + won't display a DockingEmptyBg background.
			ImGuiDockNodeFlags_RenderWindowBg = 1 << 6,   // DockSpace() will render a ImGuiCol_WindowBg background covering everything excepted the Central Node (when empty). Meaning the host window should properly use SetNextWindowBgAlpha(0.0f) + ImGuiDockNodeFlags_NoOuterBorder prior to Begin() when using this.
			ImGuiDockNodeFlags_PassthruDockspace = ImGuiDockNodeFlags_NoDockingInCentralNode | ImGuiDockNodeFlags_RenderWindowBg | ImGuiDockNodeFlags_PassthruInEmptyNodes
		};

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


		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
			
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		static ImGuiDockNodeFlags opt_flags = ImGuiDockNodeFlags_None;
		bool open = true;
		ImGui::PopStyleVar(2);
		ImGui::Begin("DockSpace Demo", &open, window_flags);
		ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), opt_flags);
		ImGui::End();

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
				if (ImGui::MenuItem("Save scene", "CTRL+S", false, true)) { XMLWriter::WriteScene(Scene::Current()); }
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
						std::shared_ptr<Component> comp = std::make_shared<TestComponent>();
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
			for (std::shared_ptr<Component> comp : Scene::SelectedGameObject()->Components())
			{
				comp->RenderInspectorInfo();
			}

			// add component button at the end of the component list
			static bool addingComponent;

			if (ImGui::Button("Add Component", ImVec2(ImGui::GetWindowSize().x - 15, 20)))
				addingComponent = true;

			if (addingComponent)
			{
				ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
				ImGui::BeginChild("Child2", ImVec2(0, 260), true);
				if (ImGui::BeginMenuBar())
				{
					if (ImGui::BeginMenu("Menu"))
					{
						ImGui::EndMenu();
					}
					ImGui::EndMenuBar();
				}
				
				ImGui::EndChild();
				ImGui::PopStyleVar();
			}
		}
		ImGui::End();
	}

	void ImGuiLayer::RenderGameWindow()
	{

		ImGui::Begin("Game");

		if (m_ShowStatistics)
		{	//TODO brol ervan tussen halen
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
		ImVec2 screenCoords = ImGui::GetCursorPos();
		ImGui::Begin("Hierarchy");

		ImGui::SetCursorPos(screenCoords);

		static int selection_mask = 0x00;   // Dumb representation of what may be user-side selection state. You may carry selection state inside or outside your objects in whatever format you see fit.

		int node_clicked = -1;
		
		unsigned int index = 0;
		for (auto go : Scene::Current()->GameObjects())
		{
			go->OnHierarchyRender(Scene::SelectedGameObject(), node_clicked, index, selection_mask);
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
		ImGui::BeginChild("test");
		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::Selectable("add new gameobject"))
			{
				AddEmptyGameObject();
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
		static int index = 0;

		if (!index)
		{
			GameObject newObject = GameObject("new gameobject");
			Scene::Current()->AddGameObject(std::make_shared<GameObject>(newObject));
		}
		else
		{
			std::stringstream name;
			name << "new gameobject(" << index << ")";
			GameObject newObject = GameObject(name.str());
			Scene::Current()->AddGameObject(std::make_shared<GameObject>(newObject));
		}
		index++;
		EN_CORE_INFO("add new gameObject");
	}
}
