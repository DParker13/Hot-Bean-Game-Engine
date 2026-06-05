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
#include <HotBeanEngine/editor/editor_gui.hpp>

#include "control_bar.hpp"
#include "menu.hpp"
#include "project_manager.hpp"

// Windows
#include "windows/config_window.hpp"
#include "windows/console_window.hpp"
#include "windows/entity_window.hpp"
#include "windows/layer_window.hpp"
#include "windows/project_window.hpp"
#include "windows/property_window.hpp"

namespace HBE::Application::GUI {
    namespace {
        void ApplyTheme() {
            ImGui::StyleColorsDark();

            ImGuiStyle &style = ImGui::GetStyle();
            style.WindowRounding = 9.0f;
            style.ChildRounding = 7.0f;
            style.FrameRounding = 6.0f;
            style.PopupRounding = 7.0f;
            style.ScrollbarRounding = 8.0f;
            style.GrabRounding = 6.0f;
            style.TabRounding = 6.0f;
            style.WindowPadding = ImVec2(10.0f, 8.0f);
            style.FramePadding = ImVec2(10.0f, 6.0f);
            style.ItemSpacing = ImVec2(8.0f, 7.0f);
            style.ItemInnerSpacing = ImVec2(7.0f, 6.0f);
            style.WindowBorderSize = 1.0f;
            style.FrameBorderSize = 0.0f;
            style.TabBorderSize = 0.0f;

            ImVec4 *colors = style.Colors;
            colors[ImGuiCol_Text] = ImVec4(0.94f, 0.95f, 0.97f, 1.00f);
            colors[ImGuiCol_TextDisabled] = ImVec4(0.54f, 0.58f, 0.63f, 1.00f);
            colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.11f, 0.13f, 1.00f);
            colors[ImGuiCol_ChildBg] = ImVec4(0.11f, 0.12f, 0.14f, 1.00f);
            colors[ImGuiCol_PopupBg] = ImVec4(0.12f, 0.13f, 0.16f, 0.98f);
            colors[ImGuiCol_Border] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
            colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.18f, 0.22f, 1.00f);
            colors[ImGuiCol_FrameBgHovered] = ImVec4(0.21f, 0.24f, 0.30f, 1.00f);
            colors[ImGuiCol_FrameBgActive] = ImVec4(0.17f, 0.34f, 0.47f, 1.00f);
            colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.09f, 0.11f, 1.00f);
            colors[ImGuiCol_TitleBgActive] = ImVec4(0.11f, 0.13f, 0.16f, 1.00f);
            colors[ImGuiCol_MenuBarBg] = ImVec4(0.09f, 0.10f, 0.12f, 1.00f);
            colors[ImGuiCol_ScrollbarBg] = ImVec4(0.07f, 0.08f, 0.10f, 1.00f);
            colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.26f, 0.29f, 0.34f, 1.00f);
            colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.31f, 0.35f, 0.41f, 1.00f);
            colors[ImGuiCol_CheckMark] = ImVec4(0.34f, 0.82f, 0.78f, 1.00f);
            colors[ImGuiCol_Button] = ImVec4(0.16f, 0.45f, 0.52f, 1.00f);
            colors[ImGuiCol_ButtonHovered] = ImVec4(0.20f, 0.54f, 0.62f, 1.00f);
            colors[ImGuiCol_ButtonActive] = ImVec4(0.14f, 0.40f, 0.46f, 1.00f);
            colors[ImGuiCol_Header] = ImVec4(0.17f, 0.43f, 0.50f, 0.90f);
            colors[ImGuiCol_HeaderHovered] = ImVec4(0.22f, 0.52f, 0.61f, 0.90f);
            colors[ImGuiCol_HeaderActive] = ImVec4(0.16f, 0.38f, 0.45f, 0.95f);
            colors[ImGuiCol_Separator] = ImVec4(0.24f, 0.27f, 0.33f, 1.00f);
            colors[ImGuiCol_ResizeGrip] = ImVec4(0.24f, 0.48f, 0.56f, 0.35f);
            colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.28f, 0.58f, 0.67f, 0.78f);
            colors[ImGuiCol_ResizeGripActive] = ImVec4(0.20f, 0.46f, 0.54f, 0.95f);
            colors[ImGuiCol_Tab] = ImVec4(0.14f, 0.16f, 0.20f, 1.00f);
            colors[ImGuiCol_TabHovered] = ImVec4(0.24f, 0.56f, 0.64f, 1.00f);
            colors[ImGuiCol_TabActive] = ImVec4(0.18f, 0.44f, 0.51f, 1.00f);
            colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.12f, 0.15f, 1.00f);
            colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.18f, 0.23f, 1.00f);
            colors[ImGuiCol_DockingPreview] = ImVec4(0.30f, 0.74f, 0.72f, 0.45f);
            colors[ImGuiCol_NavHighlight] = ImVec4(0.32f, 0.80f, 0.76f, 1.00f);
            colors[ImGuiCol_PlotLines] = ImVec4(0.56f, 0.80f, 0.89f, 1.00f);
            colors[ImGuiCol_PlotHistogram] = ImVec4(0.35f, 0.83f, 0.78f, 1.00f);
            colors[ImGuiCol_TableHeaderBg] = ImVec4(0.14f, 0.17f, 0.21f, 1.00f);
            colors[ImGuiCol_TableBorderStrong] = ImVec4(0.22f, 0.25f, 0.31f, 1.00f);
            colors[ImGuiCol_TableBorderLight] = ImVec4(0.18f, 0.20f, 0.25f, 1.00f);
            colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.03f);
            colors[ImGuiCol_TextSelectedBg] = ImVec4(0.23f, 0.61f, 0.68f, 0.35f);
        }
    } // namespace

    using namespace Core;
    using namespace Default::Components;

    EditorGUI::EditorGUI() {
        m_project_manager = std::make_shared<ProjectManager>();
        m_menu = std::make_shared<Menu>(m_windows, m_project_manager);
        m_control_bar = std::make_shared<ControlBar>();

        // Create windows
        std::shared_ptr<NewProjectWindow> new_project_window = std::make_shared<NewProjectWindow>(m_project_manager);
        std::shared_ptr<PropertyWindow> property_window = std::make_shared<PropertyWindow>();
        std::shared_ptr<EntityWindow> entity_window = std::make_shared<EntityWindow>(property_window);
        std::shared_ptr<ConsoleWindow> console_window = std::make_shared<ConsoleWindow>();
        std::shared_ptr<LayerWindow> layer_window = std::make_shared<LayerWindow>(property_window);
        std::shared_ptr<ProjectWindow> project_window = std::make_shared<ProjectWindow>(m_project_manager);
        std::shared_ptr<ConfigWindow> config_window = std::make_shared<ConfigWindow>();

        // The order of this stack determines their default docking positions (TODO: Make this configurable)
        m_windows.emplace(entity_window->m_name, entity_window);           // Left 1
        m_windows.emplace(layer_window->m_name, layer_window);             // Left 2
        m_windows.emplace(console_window->m_name, console_window);         // Bottom
        m_windows.emplace(property_window->m_name, property_window);       // Right
        m_windows.emplace(new_project_window->m_name, new_project_window); // New project dialog (not docked)
        m_windows.emplace(project_window->m_name, project_window);         // Project window (not docked)
        m_windows.emplace(config_window->m_name, config_window);           // Config window (not docked)
    }

    EditorGUI::~EditorGUI() {
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
    }

    /**
     * @brief Initializes the editor GUI by setting up ImGui context, creating windows, and applying the theme.
     * This is called after the application has initialized and is ready to set up the editor interface.
     */
    void EditorGUI::InitEditorGUI() {
        // Setup ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows
        ImGui_ImplSDL3_InitForSDLRenderer(g_app.GetWindow(), g_app.GetRenderer());
        ImGui_ImplSDLRenderer3_Init(g_app.GetRenderer());

        ApplyTheme();
    }

    void EditorGUI::OnLog(LoggingType level, std::string_view message) {
        // Forward log messages to windows that need them
        for (auto &[name, window] : m_windows) {
            if (name == "Console") {
                auto *console_window = dynamic_cast<ConsoleWindow *>(window.get());
                console_window->OnLog(level, message);
            }
        }
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
        for (auto &[name, window] : m_windows) {
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

        m_menu->Render();
        m_control_bar->Render();
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
        Camera &editor_camera = g_app.GetEditorGUI().GetEditorCamera();
        auto keys_pressed = g_app.GetInputEventListener().GetKeysPressed();

        // Keyboard input
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

        // Mouse drag input
        auto mouse_position = g_app.GetInputEventListener().GetMousePosition();
        auto mouse_buttons = g_app.GetInputEventListener().GetMouseButtonsPressed();

        bool left_button_pressed = mouse_buttons.find(SDL_BUTTON_LEFT) != mouse_buttons.end();

        if (left_button_pressed) {
            if (!m_is_dragging) {
                // Start dragging
                m_is_dragging = true;
                m_last_mouse_position = mouse_position;
            }
            else {
                // Continue dragging - calculate delta and move camera
                glm::vec2 delta = mouse_position - m_last_mouse_position;
                editor_camera_transform.m_local_position.x -= delta.x;
                editor_camera_transform.m_local_position.y -= delta.y;
                m_last_mouse_position = mouse_position;
            }
        }
        else {
            // Stop dragging
            m_is_dragging = false;
        }

        // Mouse wheel zoom
        float wheel_delta = g_app.GetInputEventListener().GetMouseWheelDelta();
        if (wheel_delta != 0.0f) {
            const float zoom_speed = 0.1f;
            float zoom_factor = 1.0f + (wheel_delta * zoom_speed);
            editor_camera.m_zoom *= zoom_factor;

            // Clamp zoom to reasonable bounds
            editor_camera.m_zoom = std::max(0.1f, std::min(10.0f, editor_camera.m_zoom));
        }
    }
} // namespace HBE::Application::GUI