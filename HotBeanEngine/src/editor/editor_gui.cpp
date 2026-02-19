/**
 * @file editor_gui.cpp
 * @author Daniel Parker (DParker13)
 * @brief Implementation of the editor GUI that integrates all editor windows.
 * Manages ImGui-based interface with docking for entity editing and debugging.
 * @version 0.1
 * @date 2025-10-30
 *
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/defaults/systems/rendering/transform_system.hpp>
#include <HotBeanEngine/editor/editor_gui.hpp>

#include "console_window.hpp"
#include "control_bar.hpp"
#include "entity_window.hpp"
#include "layer_window.hpp"
#include "menu.hpp"
#include "property_window.hpp"

namespace HBE::Application::GUI {
    using namespace HBE::Default::Components;

    EditorGUI::EditorGUI() {
        // Create windows
        std::shared_ptr<PropertyWindow> property_window = std::make_shared<PropertyWindow>();
        std::shared_ptr<EntityWindow> entity_window = std::make_shared<EntityWindow>(property_window);
        std::shared_ptr<ConsoleWindow> console_window = std::make_shared<ConsoleWindow>();
        std::shared_ptr<Menu> menu = std::make_shared<Menu>(m_windows);
        std::shared_ptr<LayerWindow> layer_window = std::make_shared<LayerWindow>(property_window);
        std::shared_ptr<ControlBar> control_bar = std::make_shared<ControlBar>();

        // The order of this stack determines their default docking positions (TODO: Make this configurable)
        m_windows.push_back(entity_window);   // Left
        m_windows.push_back(console_window);  // Bottom
        m_windows.push_back(property_window); // Right
        m_windows.push_back(menu);            // Top
        m_windows.push_back(layer_window);    // IDK
        m_windows.push_back(control_bar);     // Control Bar
    }

    EditorGUI::~EditorGUI() {
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
    }

    void EditorGUI::InitEditorGUI() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows
        ImGui_ImplSDL3_InitForSDLRenderer(g_app.GetWindow(), g_app.GetRenderer());
        ImGui_ImplSDLRenderer3_Init(g_app.GetRenderer());

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
    }

    /// @brief Handles window resize events for the editor GUI
    /// @param event The SDL event to handle
    void EditorGUI::OnWindowResize(SDL_Event &event) {
        ImGuiIO &io = ImGui::GetIO();
        io.DisplaySize = ImVec2((float)event.window.data1, (float)event.window.data2);
    }

    /// @brief Handles SDL events for the editor GUI
    /// @param event The SDL event to handle
    void EditorGUI::OnEvent(SDL_Event &event) { ImGui_ImplSDL3_ProcessEvent(&event); }

    void EditorGUI::OnUpdate() { MoveCamera(100.0f); }

    /// @brief Renders the editor GUI
    void EditorGUI::OnRender() {
        // RenderCameraViewports();
        RenderImGui();
    }

    /// @brief Renders all registered windows in the editor GUI
    void EditorGUI::RenderWindows() {
        for (auto &window : m_windows) {
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
        SDL_SetRenderDrawColor(g_app.GetRenderer(), 255, 255, 255, 255);

        std::vector<EntityID> camera_entities = g_app.GetCameraManager().GetAllActiveCameras();
        int screen_width, screen_height;
        SDL_GetRenderOutputSize(g_app.GetRenderer(), &screen_width, &screen_height);

        for (auto &camera_entity : camera_entities) {
            auto &camera = g_ecs.GetComponent<Camera>(camera_entity);
            auto &camera_transform = g_ecs.GetComponent<Transform2D>(camera_entity);
            SDL_FRect viewport =
                SDL_FRect{camera.m_viewport_position.x +
                              g_app.GetCameraManager()
                                  .CalculateScreenPosition(camera, GetEditorCameraTransform(), camera_transform)
                                  .x,
                          camera.m_viewport_position.y +
                              g_app.GetCameraManager()
                                  .CalculateScreenPosition(camera, GetEditorCameraTransform(), camera_transform)
                                  .y,
                          camera.m_viewport_size.x * screen_width, camera.m_viewport_size.y * screen_height};
            SDL_RenderRect(g_app.GetRenderer(), &viewport);
        }
    }

    void EditorGUI::MoveCamera(float speed) {
        Transform2D &editor_camera_transform = g_app.GetEditorGUI().GetEditorCameraTransform();
        auto keys_pressed = g_app.GetInputEventListener().GetKeysPressed();

        if (keys_pressed.size() > 0) {
            float distance = speed * g_app.GetDeltaTime();

            if (keys_pressed.find(SDLK_LEFT) != keys_pressed.end()) {
                editor_camera_transform.m_local_position.x -= distance;
            }

            if (keys_pressed.find(SDLK_RIGHT) != keys_pressed.end()) {
                editor_camera_transform.m_local_position.x += distance;
            }

            if (keys_pressed.find(SDLK_UP) != keys_pressed.end()) {
                editor_camera_transform.m_local_position.y -= distance;
            }

            if (keys_pressed.find(SDLK_DOWN) != keys_pressed.end()) {
                editor_camera_transform.m_local_position.y += distance;
            }
        }
    }
} // namespace HBE::Application::GUI