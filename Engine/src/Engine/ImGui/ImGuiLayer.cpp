#include  "enpch.h" 
#include  "ImGuiLayer.h" 

#include  "imgui.h" 

#include  "examples/imgui_impl_glfw.h" 
#include  "examples/imgui_impl_opengl3.h" 

// TEMP
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include  "Engine/GameObject.h" 

#include  "Engine/Application.h"

#include  "Engine/Logic/Scene.h" 

//
//#include  imgui_internal.h 

namespace Engine {

	//-----------------------------------------------------------------------------
// [SECTION] Example App: Debug Console / ShowExampleAppConsole()
//-----------------------------------------------------------------------------

// Demonstrate creating a simple console window, with scrolling, filtering, completion and history.
// For the console example, here we are using a more C++ like approach of declaring a class to hold the data and the functions.
	struct ExampleAppConsole
	{
		char                  InputBuf[256];
		ImVector<char*>       Items;
		bool                  ScrollToBottom;
		ImVector<char*>       History;
		int                   HistoryPos;    // -1: new line, 0..History.Size-1 browsing history.
		ImVector<const char*> Commands;

		ExampleAppConsole()
		{
			ClearLog();
			memset(InputBuf, 0, sizeof(InputBuf));
			HistoryPos = -1;
			Commands.push_back("HELP");
			Commands.push_back("HISTORY");
			Commands.push_back("CLEAR");
			Commands.push_back("CLASSIFY");  // "classify" is only here to provide an example of "C"+[tab] completing to "CL" and displaying matches.
			AddLog("Welcome to Dear ImGui!");
		}
		~ExampleAppConsole()
		{
			ClearLog();
			for (int i = 0; i < History.Size; i++)
				free(History[i]);
		}

		// Portable helpers
		static int   Stricmp(const char* str1, const char* str2) { int d; while ((d = toupper(*str2) - toupper(*str1)) == 0 && *str1) { str1++; str2++; } return d; }
		static int   Strnicmp(const char* str1, const char* str2, int n) { int d = 0; while (n > 0 && (d = toupper(*str2) - toupper(*str1)) == 0 && *str1) { str1++; str2++; n--; } return d; }
		static char* Strdup(const char *str) { size_t len = strlen(str) + 1; void* buff = malloc(len); return (char*)memcpy(buff, (const void*)str, len); }
		static void  Strtrim(char* str) { char* str_end = str + strlen(str); while (str_end > str && str_end[-1] == ' ') str_end--; *str_end = 0; }

		void    ClearLog()
		{
			for (int i = 0; i < Items.Size; i++)
				free(Items[i]);
			Items.clear();
			ScrollToBottom = true;
		}

		void    AddLog(const char* fmt, ...) IM_FMTARGS(2)
		{
			// FIXME-OPT
			char buf[1024];
			va_list args;
			va_start(args, fmt);
			vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
			buf[IM_ARRAYSIZE(buf) - 1] = 0;
			va_end(args);
			Items.push_back(Strdup(buf));
			ScrollToBottom = true;
		}

		void    Draw(const char* title, bool* p_open)
		{
			ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
			if (!ImGui::Begin(title, p_open))
			{
				ImGui::End();
				return;
			}

			if (ImGui::BeginPopupContextItem())
			{
				if (ImGui::MenuItem( "Close Console" ))
					*p_open = false;
				ImGui::EndPopup();
			}

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
			/*static ImGuiTextFilter filter;
			filter.Draw( Filter (\ incl,-excl\ ) (\ error\ ) , 180);*/
			ImGui::PopStyleVar();
			/*ImGui::Separator();*/

			const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing(); // 1 separator, 1 input text
			ImGui::BeginChild( "ScrollingRegion" , ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar); // Leave room for 1 separator + 1 InputText
			if (ImGui::BeginPopupContextWindow())
			{
				if (ImGui::Selectable( "Clear" )) ClearLog();
				ImGui::EndPopup();
			}

			// Display every line as a separate entry so we can change their color or add custom widgets. If you only want raw text you can use ImGui::TextUnformatted(log.begin(), log.end());
			// NB- if you have thousands of entries this approach may be too inefficient and may require user-side clipping to only process visible items.
			// You can seek and display only the lines that are visible using the ImGuiListClipper helper, if your elements are evenly spaced and you have cheap random access to the elements.
			// To use the clipper we could replace the 'for (int i = 0; i < Items.Size; i++)' loop with:
			//     ImGuiListClipper clipper(Items.Size);
			//     while (clipper.Step())
			//         for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
			// However, note that you can not use this code as is if a filter is active because it breaks the 'cheap random-access' property. We would need random-access on the post-filtered list.
			// A typical application wanting coarse clipping and filtering may want to pre-compute an array of indices that passed the filtering test, recomputing this array when user changes the filter,
			// and appending newly elements as they are inserted. This is left as a task to the user until we can manage to improve this example code!
			// If your items are of variable size you may want to implement code similar to what ImGuiListClipper does. Or split your data into fixed height items to allow random-seeking into your list.
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
			
			ImVec4 col_default_text = ImGui::GetStyleColorVec4(ImGuiCol_Text);
			for (int i = 0; i < Items.Size; i++)
			{
				const char* item = Items[i];
				/*if (!filter.PassFilter(item))
					continue;*/
				ImVec4 col = col_default_text;
				if (strstr(item,  "[error]" )) col = ImColor(1.0f, 0.4f, 0.4f, 1.0f);
				else if (strncmp(item,  "# " , 2) == 0) col = ImColor(1.0f, 0.78f, 0.58f, 1.0f);
				ImGui::PushStyleColor(ImGuiCol_Text, col);
				ImGui::TextUnformatted(item);
				ImGui::PopStyleColor();
			}
			
			if (ScrollToBottom)
				ImGui::SetScrollHereY(1.0f);
			ScrollToBottom = false;
			ImGui::PopStyleVar();
			ImGui::EndChild();
			ImGui::Separator();

			// Command-line
			bool reclaim_focus = false;
			if (ImGui::InputText( "input" , InputBuf, IM_ARRAYSIZE(InputBuf), ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory, &TextEditCallbackStub, (void*)this))
			{
				char* s = InputBuf;
				Strtrim(s);
				if (s[0])
					ExecCommand(s);
				strcpy(s, " " );
				reclaim_focus = true;
			}

			// Auto-focus on window apparition
			ImGui::SetItemDefaultFocus();
			if (reclaim_focus)
				ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget

			ImGui::End();
		}

		void    ExecCommand(const char* command_line)
		{
			AddLog( "# %s\n" , command_line);

			// Insert into history. First find match and delete it so it can be pushed to the back. This isn't trying to be smart or optimal.
			HistoryPos = -1;
			for (int i = History.Size - 1; i >= 0; i--)
				if (Stricmp(History[i], command_line) == 0)
				{
					free(History[i]);
					History.erase(History.begin() + i);
					break;
				}
			History.push_back(Strdup(command_line));

			// Process command
			if (Stricmp(command_line,  "CLEAR" ) == 0)
			{
				ClearLog();
			}
			else if (Stricmp(command_line,  "HELP" ) == 0)
			{
				AddLog( "Commands: ");
				for (int i = 0; i < Commands.Size; i++)
					AddLog( "- %s" , Commands[i]);
			}
			else if (Stricmp(command_line,  "HISTORY" ) == 0)
			{
				int first = History.Size - 10;
				for (int i = first > 0 ? first : 0; i < History.Size; i++)
					AddLog( "%3d: %s\n ", i, History[i]);
			}
			else
			{
				AddLog( "Unknown command: '%s'\n" , command_line);
			}
		}

		static int TextEditCallbackStub(ImGuiInputTextCallbackData* data) // In C++11 you are better off using lambdas for this sort of forwarding callbacks
		{
			ExampleAppConsole* console = (ExampleAppConsole*)data->UserData;
			return console->TextEditCallback(data);
		}

		int     TextEditCallback(ImGuiInputTextCallbackData* data)
		{
			//AddLog( cursor: %d, selection: %d-%d , data->CursorPos, data->SelectionStart, data->SelectionEnd);
			switch (data->EventFlag)
			{
			case ImGuiInputTextFlags_CallbackCompletion:
			{
				// Example of TEXT COMPLETION

				// Locate beginning of current word
				const char* word_end = data->Buf + data->CursorPos;
				const char* word_start = word_end;
				while (word_start > data->Buf)
				{
					const char c = word_start[-1];
					if (c == ' ' || c == '\t' || c == ',' || c == ';')
						break;
					word_start--;
				}

				// Build a list of candidates
				ImVector<const char*> candidates;
				for (int i = 0; i < Commands.Size; i++)
					if (Strnicmp(Commands[i], word_start, (int)(word_end - word_start)) == 0)
						candidates.push_back(Commands[i]);

				if (candidates.Size == 0)
				{
					// No match
					AddLog( "No match for \ %.*s\ !\n" , (int)(word_end - word_start), word_start);
				}
				else if (candidates.Size == 1)
				{
					// Single match. Delete the beginning of the word and replace it entirely so we've got nice casing
					data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
					data->InsertChars(data->CursorPos, candidates[0]);
					data->InsertChars(data->CursorPos,  ""  );
				}
				else
				{
					// Multiple matches. Complete as much as we can, so inputing  C  will complete to  CL  and display  CLEAR  and  CLASSIFY 
					int match_len = (int)(word_end - word_start);
					for (;;)
					{
						int c = 0;
						bool all_candidates_matches = true;
						for (int i = 0; i < candidates.Size && all_candidates_matches; i++)
							if (i == 0)
								c = toupper(candidates[i][match_len]);
							else if (c == 0 || c != toupper(candidates[i][match_len]))
								all_candidates_matches = false;
						if (!all_candidates_matches)
							break;
						match_len++;
					}

					if (match_len > 0)
					{
						data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
						data->InsertChars(data->CursorPos, candidates[0], candidates[0] + match_len);
					}

					// List matches
					AddLog( "Possible matches:\n" );
					for (int i = 0; i < candidates.Size; i++)
						AddLog( "- %s\n" , candidates[i]);
				}

				break;
			}
			case ImGuiInputTextFlags_CallbackHistory:
			{
				// Example of HISTORY
				const int prev_history_pos = HistoryPos;
				if (data->EventKey == ImGuiKey_UpArrow)
				{
					if (HistoryPos == -1)
						HistoryPos = History.Size - 1;
					else if (HistoryPos > 0)
						HistoryPos--;
				}
				else if (data->EventKey == ImGuiKey_DownArrow)
				{
					if (HistoryPos != -1)
						if (++HistoryPos >= History.Size)
							HistoryPos = -1;
				}

				// A better implementation would preserve the data on the current input line along with cursor position.
				if (prev_history_pos != HistoryPos)
				{
					const char* history_str = (HistoryPos >= 0) ? History[HistoryPos] : "" ;
					data->DeleteChars(0, data->BufTextLen);
					data->InsertChars(0, history_str);
				}
			}
			}
			return 0;
		}
	};

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
		static ExampleAppConsole console;
		bool open = true;
		console.Draw( "Example: Console" , &open);
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
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

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
					ImGui::EndMenu();
				}
				else
				{
					if (ImGui::MenuItem( "enable Statistics" )) { ToggleStatistics(); }
					ImGui::EndMenu();
				}
				
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

		

		ImGui::End();
	}

	void ImGuiLayer::RenderSceneWindow()
	{
		ImGui::Begin( "Scene" );

		ImVec2 startPos = ImGui::GetCursorScreenPos();
		ImVec2 size = ImGui::GetWindowSize();
		ImVec2 endPos = ImVec2(startPos.x + size.x, startPos.y + size.y);
		ImTextureID texID = (void*)(2);
		ImGui::GetWindowDrawList()->AddImage(texID, startPos, ImVec2(startPos.x + size.x, startPos.y + size.y), ImVec2(0, 1), ImVec2(1, 0));

		ImGui::End();
	}

	void ImGuiLayer::RenderGameWindow()
	{

		ImGui::Begin( "Game" );

		ImVec2 startPos = ImGui::GetCursorScreenPos();
		ImVec2 size = ImGui::GetWindowSize();
		ImVec2 endPos = ImVec2(startPos.x + size.x, startPos.y + size.y);
		ImTextureID texID = (void*)(1);
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
					ImGui::Text( "Moving \ %s\"  , names[n]");
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
