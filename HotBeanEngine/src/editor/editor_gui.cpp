#include <HotBeanEngine/editor/editor_gui.hpp>
#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/defaults/systems/rendering/transform_system.hpp>

#include "entity_window.hpp"
#include "console_window.hpp"
#include "menu.hpp"
#include "property_window.hpp"
#include "control_bar.hpp"
#include "layer_window.hpp"

namespace HBE::Application::GUI {
    EditorGUI::EditorGUI() {
        // Create windows
        std::shared_ptr<PropertyWindow> property_window = std::make_shared<PropertyWindow>();
        std::shared_ptr<EntityWindow> entity_window = std::make_shared<EntityWindow>(property_window);
        std::shared_ptr<ConsoleWindow> console_window = std::make_shared<ConsoleWindow>();
        std::shared_ptr<Menu> menu = std::make_shared<Menu>(m_windows);
        std::shared_ptr<LayerWindow> layer_window = std::make_shared<LayerWindow>(property_window);
        std::shared_ptr<ControlBar> control_bar = std::make_shared<ControlBar>();

        // The order of this stack determines their default docking positions (TODO: Make this configurable)
        m_windows.push_back(entity_window); // Left
        m_windows.push_back(console_window); // Bottom
        m_windows.push_back(property_window); // Right
        m_windows.push_back(menu); // Top
        m_windows.push_back(layer_window); // IDK
        m_windows.push_back(control_bar); // Control Bar
        
    }

    EditorGUI::~EditorGUI() {
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
    }

    void EditorGUI::InitEditorGUI() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
        ImGui_ImplSDL3_InitForSDLRenderer(g_app.GetWindow(), g_app.GetRenderer());
        ImGui_ImplSDLRenderer3_Init(g_app.GetRenderer());

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
    }

    /// @brief Handles window resize events for the editor GUI
    /// @param event The SDL event to handle
    void EditorGUI::OnWindowResize(SDL_Event& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2((float)event.window.data1, (float)event.window.data2);
    }

    /// @brief Handles SDL events for the editor GUI
    /// @param event The SDL event to handle
    void EditorGUI::OnEvent(SDL_Event& event) {
        HandleInput(event);

        ImGui_ImplSDL3_ProcessEvent(&event);
    }

    /// @brief Renders the editor GUI
    void EditorGUI::OnRender() {
        RenderCameraViewports();
        RenderImGui();
    }

    /// @brief Renders all registered windows in the editor GUI
    void EditorGUI::RenderWindows() {
        for (auto& window : m_windows) {
            if (window->m_open) {
                window->RenderWindow();
            }
        }
    }

    /// @brief Renders the ImGui interface for the editor GUI
    void EditorGUI::RenderImGui() {
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        SetupDefaultDockingLayout();

        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()->ID, nullptr, ImGuiDockNodeFlags_PassthruCentralNode);

        RenderWindows();

        // Rendering
        ImGui::Render();
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), g_app.GetRenderer());
    }

    void EditorGUI::SetupDefaultDockingLayout() {
        // ImGuiID dockspace_id = ImGui::GetID("Default Dockspace");
        // ImGuiViewport* viewport = ImGui::GetMainViewport();

        // // Create default dockspace settings
        // if (ImGui::DockBuilderGetNode(dockspace_id) == nullptr)
        // {
        //     ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
        //     ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);
        //     ImGuiID dock_id_left = 0;
        //     ImGuiID dock_id_main = dockspace_id;
        //     ImGui::DockBuilderSplitNode(dock_id_main, ImGuiDir_Left, 0.20f, &dock_id_left, &dock_id_main);
        //     ImGuiID dock_id_left_top = 0;
        //     ImGuiID dock_id_left_bottom = 0;
        //     ImGui::DockBuilderSplitNode(dock_id_left, ImGuiDir_Down, 0.50f, &dock_id_left_top, &dock_id_left_bottom);
        //     ImGui::DockBuilderDockWindow(m_windows[0]->m_name.c_str(), dock_id_main);
        //     ImGui::DockBuilderDockWindow(m_windows[1]->m_name.c_str(), dock_id_left_top);
        //     ImGui::DockBuilderDockWindow(m_windows[2]->m_name.c_str(), dock_id_left_bottom);
        //     ImGui::DockBuilderFinish(dockspace_id);
        // }
    }

    void EditorGUI::RenderCameraViewports() {
        auto* camera_system = g_ecs.GetSystem<HBE::Default::Systems::CameraSystem>();

        if (!camera_system) {
            return;
        }

        SDL_SetRenderDrawColor(g_app.GetRenderer(), 255, 255, 255, 255);

        std::vector<EntityID> camera_entities = camera_system->GetAllActiveCameras();

        for (auto& camera_entity : camera_entities) {
            SDL_FRect viewport = camera_system->GetViewport(camera_entity);
            SDL_RenderRect(g_app.GetRenderer(), &viewport);
        }
    }

    void EditorGUI::HandleInput(SDL_Event& event) {
        MoveEditorCamera(event, 100.0f);
    }

    void EditorGUI::MoveEditorCamera(SDL_Event& event, float speed) {
        const auto& keys_pressed = g_app.GetInputEventListener().GetKeysPressed();

        if (keys_pressed.size() > 0) {
            float distance = speed * g_app.GetDeltaTime();
            glm::vec2 offset(0.0f, 0.0f);

            if (keys_pressed.find(SDLK_LEFT) != keys_pressed.end()) {
                offset.x += distance;
            }
            
            if (keys_pressed.find(SDLK_RIGHT) != keys_pressed.end()) {
                offset.x -= distance;
            }
            
            if (keys_pressed.find(SDLK_UP) != keys_pressed.end()) {
                offset.y += distance;
            }
            
            if (keys_pressed.find(SDLK_DOWN) != keys_pressed.end()) {
                offset.y -= distance;
            }
            
            // Move all entities by the offset
            if (offset.x != 0.0f || offset.y != 0.0f) {
                auto* transform_system = g_ecs.GetSystem<HBE::Default::Systems::TransformSystem>();

                // TODO: Only do this for the editor camera(s). Right now, it moves all Transform2D components, so it looks like nothing is moving.

                if (transform_system) {
                    auto& scene_graph = transform_system->GetSceneGraph();
                    
                    // Iterate through all levels and update transforms
                    for (auto& level : scene_graph.GetAllLevels()) {
                        for (auto& entity : level.second) {
                            auto& transform = g_ecs.GetComponent<Transform2D>(entity);
                            
                            // Get parent transform if it exists
                            const Transform2D* parent_transform = nullptr;
                            if (transform.m_parent != -1) {
                                parent_transform = &g_ecs.GetComponent<Transform2D>(transform.m_parent);
                            }
                            else {
                                transform.m_local_position += offset;
                            }
                            
                            // Propagate transforms
                            TransformHelper::PropagateTransforms(transform, parent_transform);
                        }
                    }
                }
            }
        }
    }
}