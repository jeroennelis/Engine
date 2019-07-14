#include  "enpch.h" 
#include  "ImGuiLayer.h" 

#include  "imgui.h" 

#include  "examples/imgui_impl_glfw.h" 
#include  "examples/imgui_impl_opengl3.h" 

// TEMP
#include <GLFW/glfw3.h>

#include  "Engine/GameObject.h" 

#include  "Engine/Application.h"

#include  "Engine/Logic/Scene.h" 
#include "Engine/Components/Transform.h"
#include "Platform/OpenGl/MeshRenderer.h"

#include "Platform/OpenGl/OBJLoader.h"
#include "Platform/OpenGl/FrameBuffer.h"
#include "Platform/OpenGl/Loader.h"
#include "Engine/Logic/Scene.h"
#include "Engine/Components/Camera.h"

#include "Platform/RayTracer/World/World.h"

//
//#include  imgui_internal.h 

namespace Engine {

	
	glm::vec3 ImGuiLayer::PickMouse(int windowPosX, int windowPosY, int imGuiWindowWidth, int imGuiWindowHeigth, int mouseX, int mouseY)
	{
		//Step 1: 3d Normalised Device Coordinates
		float x = 2.0f * (mouseX - windowPosX) / imGuiWindowWidth - 1.0f;
		float y = 1.0f - (2.0f * (mouseY - windowPosY)) / imGuiWindowHeigth;
		float z = 1.0f;

		//Step 2: 4d Homogeneous Clip Coordinates
		glm::vec4 vec(x, y, -1.0f, 1.0f);
				
		Camera* cam = Scene::Current()->GetSceneCamera();
		glm::vec4 ray_eye = glm::inverse(cam->GetProjectionMatrix()) * vec;
		
		ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);
		glm::vec4 ray_world = glm::inverse(cam->GetViewMatrix()) * ray_eye;
		ray_world = glm::normalize(ray_world);

		return  glm::vec3(ray_world.x, ray_world.y, ray_world.z);
	}

	bool ImGuiLayer::m_ShowStatistics = true;

	ImGuiLayer::ImGuiLayer()
		:Layer( "ImGui Layer" )
	{
		
	}
	ImGuiLayer::~ImGuiLayer()
	{
	}
	void ImGuiLayer::OnAttach()
	{
		//Setup ImGUI context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		
		// Setup ImGui style
		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init( "#version 410" ); 

		for (OpenGLMaterial* mat : Loader::Get()->GetMaterials())
		{
			mat->RenderPreview();
		}

		for (std::pair<std::string, RawModel*> model : Loader::Get()->GetRawModels())
		{
			model.second->RenderPreview();
		}
		EN_CORE_INFO( "attached imGui layer" );
	}
	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnImGuiRender()
	{
		RenderMenuBar();
		RenderHierarchyWindow();
		RenderGameWindow();
		RenderSceneWindow();
		RenderInspectorWindow();
		RenderConsoleWindow();
		RenderProjectWindow();
		bool open = true;
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
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
		ImGui::Begin( "DockSpace Demo" , &open, window_flags);
		ImGuiID dockspace_id = ImGui::GetID( "MyDockspace" );
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), opt_flags);
		ImGui::End();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiLayer::RT()
	{
		EN_CORE_INFO("tracing scene!");
		World w;
		w.build(*Scene::Current());
		//w.render_scene(std::string("test"));
		//w.render_perspective(std::string("test"));
		w.camera_ptr->render_scene(&w);
		w.SaveImage("test.png");
		
		EN_CORE_INFO("tracing complete!");
		test.joinable();
	}

	void ImGuiLayer::RenderMenuBar()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu( "File" ))
			{
				if (ImGui::MenuItem( "New Scene" ,  "CTRL+N" , false, false)) {}
				if (ImGui::MenuItem( "Open Scene" ,  "CTRL+O" , false, false)) {}
				ImGui::Separator();	 
				if (ImGui::MenuItem( "Save scene" ,  "CTRL+S" , false, true)) { XMLWriter::WriteScene(Scene::Current()); }
				if (ImGui::MenuItem( "Save As..." ,  "CTRL+SHIFT+N" , false, false)) {}
				ImGui::Separator();	 
				if (ImGui::MenuItem( "New Project" , ""  , false, false)) {}
				if (ImGui::MenuItem( "Open Project" , ""  , false, false)) {}
				if (ImGui::MenuItem( "Save Project" , ""  , false, false)) {}
				if (ImGui::MenuItem( "trace scene", "", false, true)) 
				{
					RT();
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu( "Edit" ))
			{
				if (ImGui::MenuItem( "Undo" ,  "CTRL+Z" , false, false)) {}
				if (ImGui::MenuItem( "Redo" ,  "CTRL+Y" , false, false)) {}  // Disabled item
				ImGui::Separator();
				if (ImGui::MenuItem( "Cut" ,  "CTRL+X" , false, false)) {}
				if (ImGui::MenuItem( "Copy" ,  "CTRL+C" , false, false)) {}
				if (ImGui::MenuItem( "Paste" ,  "CTRL+V" , false, false)) {}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu( "Assets" ))
			{
				if (ImGui::MenuItem( "Undo" ,  "CTRL+Z" , false, false)) {}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu( "GameObject" ))
			{
				if (ImGui::MenuItem( "Create Empty" ,  "CTRL+SHIFT+N" )) { AddEmptyGameObject(); }
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu( "Component" ))
			{
				bool enabled = false;
				if (Scene::Current()->SelectedGameObject())
					enabled = true;

				if (ImGui::BeginMenu( "Test" ))
				{
					if (ImGui::MenuItem( "Test Component" , ""  , false, enabled)) 
					{
						std::shared_ptr<Component> comp = std::make_shared<TestComponent>();
						Scene::Current()->SelectedGameObject()->AddComponent(comp);
					}
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu( "Window" ))
			{
				
				if (m_ShowStatistics)
				{
					if (ImGui::MenuItem( "disable Statistics" )) { ToggleStatistics(); }
				}
				else
				{
					if (ImGui::MenuItem( "enable Statistics" )) { ToggleStatistics(); }
				}
				if (ImGui::MenuItem("start physics simmulation")) { Scene::Current()->RunPhysics(); }
				ImGui::EndMenu();

				


				
			}

			ImGui::EndMainMenuBar();
		}
	}

	void ImGuiLayer::RenderInspectorWindow()
	{
		ImGui::Begin( "Inspector" );
		
		if (Scene::SelectedGameObject())
		{
			for (std::shared_ptr<Component> comp : Scene::SelectedGameObject()->Components())
			{
				comp->RenderInspectorInfo();
			}

			//add component button at the end of the component list
			static bool addingComponent;

			if (ImGui::Button( "Add Component" , ImVec2(ImGui::GetWindowSize().x - 15, 20)))
				addingComponent = true;

			if (addingComponent)
			{
				ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
				ImGui::BeginChild( "Child2" , ImVec2(0, 260), true);
				if (ImGui::BeginMenuBar())
				{
					if (ImGui::BeginMenu( "Menu" ))
					{
						ImGui::EndMenu();
					}
					ImGui::EndMenuBar();
				}
				
				ImGui::EndChild();
				ImGui::PopStyleVar();
			}
		}
		if (Scene::SelectedMaterial())
		{
			Scene::SelectedMaterial()->RenderInspectorInfo();
		}
		

		ImGui::End();
	}

	void ImGuiLayer::RenderSceneWindow()
	{
		ImGui::Begin( "Scene" );

		ImGui::BeginChild("scenewindow");
		


		ImVec2 startPos = ImGui::GetCursorScreenPos();
		ImVec2 windowPos = ImGui::GetWindowPos();
		ImVec2 size = ImGui::GetWindowSize();
		ImVec2 mousePos = ImGui::GetMousePos();

		

		ImVec2 endPos = ImVec2(startPos.x + size.x, startPos.y + size.y);
		ImTextureID texID = (ImTextureID)(Renderer::Get()->GetSceneFrameBufferTexture());
		//ImTextureID texID = (ImTextureID)14;
		ImGui::GetWindowDrawList()->AddImage(texID, startPos, ImVec2(startPos.x + size.x, startPos.y + size.y), ImVec2(0, 1), ImVec2(1, 0));


		ImGui::EndChild();
		if (ImGui::BeginDragDropTarget())
		{
			ImGuiDragDropFlags target_flags = 0;
			target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;    // Don't wait until the delivery (release mouse button on a target) to do something
			target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect; // Don't display the yellow rectangle
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Model", target_flags))
			{
				if (!ImGui::IsMouseDown(0))
				{
					glm::vec3 vector = PickMouse((int)windowPos.x, (int)windowPos.y, (int)size.x, (int)size.y, (int)mousePos.x, (int)mousePos.y);
					glm::vec3 camPos = Scene::Current()->GetSceneCamera()->GetTransform()->Position;
					glm::vec3 point = (vector * 10.0f) - camPos;
					GameObject* go = Scene::Current()->AddRawModel(Loader::Get()->SelectedRawModel());
					go->GetComponent<Transform>()->Position = point;
				}
			}
			ImGui::EndDragDropTarget();
		}
		ImGui::End();
	}

	void ImGuiLayer::RenderGameWindow()
	{
		
		ImGui::Begin( "Game" );
		
		ImGui::BeginChild("testing");
		
		ImVec2 startPos = ImGui::GetCursorScreenPos();
		ImVec2 size = ImGui::GetWindowSize();
		ImVec2 endPos = ImVec2(startPos.x + size.x, startPos.y + size.y);
		ImTextureID texID = (ImTextureID)(Renderer::Get()->GetGameFrameBufferTexture());
		ImGui::GetWindowDrawList()->AddImage(texID, startPos, ImVec2(startPos.x + size.x, startPos.y + size.y), ImVec2(0, 1), ImVec2(1, 0));
		

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
			ImGui::BeginChild( "test" , ImVec2(200, 100), m_ShowStatistics, (corner != -1 ? ImGuiWindowFlags_NoMove : 0) | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav);
			ImGui::Text(" Frame rate: %0.1f fps" , ImGui::GetIO().Framerate);
			ImGui::Indent(84);
			ImGui::Text(" %.3f ms/frame" , 1000.0f / ImGui::GetIO().Framerate);
			ImGui::EndChild();
			
		}
		ImGui::EndChild();
		ImGui::End();
	}

	void ImGuiLayer::RenderHierarchyWindow()
	{
		ImVec2 screenCoords = ImGui::GetCursorPos();
		ImGui::Begin( "Hierarchy" );

		ImGui::SetCursorPos(screenCoords);

		static int selection_mask = 0x00;   // Dumb representation of what may be user-side selection state. You may carry selection state inside or outside your objects in whatever format you see fit.

		int node_clicked = -1;
		
		unsigned int index = 0;
		for (auto go : Scene::Current()->GameObjects())
		{
			if(go)
				go->OnHierarchyRender(Scene::SelectedGameObject(), node_clicked, index, selection_mask);
		}

		if (node_clicked != -1)
		{
			 //Update selection state. Process outside of tree loop to avoid visual inconsistencies during the clicking-frame.
			if (ImGui::GetIO().KeyCtrl)
				selection_mask ^= (1 << node_clicked);  // CTRL+click to toggle
			else
			{
				selection_mask = (1 << node_clicked);   // Click to single-select
			}

		}
		ImGui::BeginChild( "test" );
		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::Selectable( "add new gameobject" ))
			{
				AddEmptyGameObject();
			}
			
			if (ImGui::Selectable("add target"))
			{
				Scene::Current()->AddCube();
			}

			if (ImGui::Selectable("add killhouse"))
			{
				Scene::Current()->AddSphere();
			}
			ImGui::EndPopup();
		}
		ImGui::EndChild();
			
		

		

		ImGui::End();

		
	}

	void ImGuiLayer::RenderConsoleWindow()
	{
		ImGui::Begin( "Console" );
		ImGui::BulletText( "Drag and drop to re-order" );
		ImGui::Indent();
		static const char* names[6] = { " 1. Adbul" ,  "2. Alfonso" ,  "3. Aline" ,  "4. Amelie" ,  "5. Anna" ,  "6. Arthur"  };
		int move_from = -1, move_to = -1;

		for (int n = 0; n < IM_ARRAYSIZE(names); n++)
		{
			if (ImGui::TreeNode(names[n]))
			{
				char label[] =  "this" ;
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
					ImGui::Text( "Moving %s"  , names[n]);
				ImGui::SetDragDropPayload( "DND_DEMO_NAME" , &n, sizeof(int));
				ImGui::EndDragDropSource();
			}
			
				

			if (ImGui::BeginDragDropTarget())
			{
				ImGuiDragDropFlags target_flags = 0;
				target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;    // Don't wait until the delivery (release mouse button on a target) to do something
				target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect; // Don't display the yellow rectangle
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload( "DND_DEMO_NAME" , target_flags))
				{
					move_from = *(const int*)payload->Data;
					move_to = n;
				}
				ImGui::EndDragDropTarget();
			}
				
		}
		

		if (move_from != -1 && move_to != -1)
		{
			//Reorder items
			int copy_dst = (move_from < move_to) ? move_from : move_to + 1;
			int copy_src = (move_from < move_to) ? move_from + 1 : move_to;
			int copy_count = (move_from < move_to) ? move_to - move_from : move_from - move_to;
			const char* tmp = names[move_from];
			printf( "[%05d] move %d->%d (copy %d..%d to %d..%d)\n" , ImGui::GetFrameCount(), move_from, move_to, copy_src, copy_src + copy_count - 1, copy_dst, copy_dst + copy_count - 1);
			memmove(&names[copy_dst], &names[copy_src], (size_t)copy_count * sizeof(const char*));
			names[move_to] = tmp;
			ImGui::SetDragDropPayload( "DND_DEMO_NAME" , &move_to, sizeof(int)); // Update payload immediately so on the next frame if we move the mouse to an earlier item our index payload will be correct. This is odd and showcase how the DnD api isn't best presented in this example.
		}
		ImGui::Unindent();


		ImGui::End();
	}

	void ImGuiLayer::RenderProjectWindow()
	{
		ImGui::Begin("Materials");
		int ypos = 25;
		int xpos = 25;
		int index = 0;
		for (OpenGLMaterial* mat: Loader::Get()->GetMaterials())
		{
			xpos = 25 + (index % 10) * 75;
			ypos = 25 + (index / 10) * 75;
			ImGui::SetCursorPos(ImVec2((float)xpos, (float)ypos));
			mat->RenderProjectInfo();
			index++;
		}
			

		ImGui::End();

		ImGui::Begin("Objects");
		ypos = 25;
		xpos = 25;
		index = 0;
		for (std::pair<std::string, RawModel*> model : Loader::Get()->GetRawModels())
		{
			xpos = 25 + (index % 10) * 75;
			ypos = 25 + (index / 10) * 75;
			ImGui::SetCursorPos(ImVec2((float)xpos, (float)ypos));
			model.second->RenderProjectInfo();
			index++;
		}

		//ImTextureID texID = (void*)1;
		//bool clicked = ImGui::ImageButton(texID, ImVec2(50, 50)); //TODO imgui pop

		//if (ImGui::BeginDragDropSource())
		//{
		//	ImGui::SetDragDropPayload("obj", "test", 5);
		//	ImGui::EndDragDropSource();
		//	
		//}
		ImGui::End();
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
			GameObject newObject = GameObject( "new gameobject" );
			Scene::Current()->AddGameObject(std::make_shared<GameObject>(newObject));
		}
		else
		{
			std::stringstream name;
			name <<  "new gameobject("  << index <<  ")" ;
			GameObject newObject = GameObject(name.str());
			Scene::Current()->AddGameObject(std::make_shared<GameObject>(newObject));
		}
		index++;
		EN_CORE_INFO( "add new gameObject" );
	}
}
