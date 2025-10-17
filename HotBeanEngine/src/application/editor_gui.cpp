#include <HotBeanEngine/application/editor_gui.hpp>
#include <HotBeanEngine/application/application.hpp>

#include "editor_gui/components_window.hpp"
#include "editor_gui/console_window.hpp"
#include "editor_gui/menu.hpp"

namespace HBE::Application::GUI {
    EditorGUI::EditorGUI() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
        ImGui_ImplSDL3_InitForSDLRenderer(g_app.GetWindow(), g_app.GetRenderer());
        ImGui_ImplSDLRenderer3_Init(g_app.GetRenderer());

        ImGui::GetStyle().Colors[ImGuiCol_WindowBg].w = 0.0f;
        ImGui::StyleColorsDark();

        m_windows.push_back(std::make_shared<Menu>(m_windows));
        m_windows.push_back(std::make_shared<ComponentsWindow>());
        m_windows.push_back(std::make_shared<ConsoleWindow>());
    }

    EditorGUI::~EditorGUI() {
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
    }

    void EditorGUI::OnWindowResize(SDL_Event& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2((float)event.window.data1, (float)event.window.data2);
    }

    void EditorGUI::OnEvent(SDL_Event& event) {
        ImGui_ImplSDL3_ProcessEvent(&event);
    }

    void EditorGUI::OnRender() {
        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()->ID, nullptr, ImGuiDockNodeFlags_PassthruCentralNode);

        RenderWindows();

        // Rendering
        ImGui::Render();
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), g_app.GetRenderer());
    }

    void EditorGUI::RenderWindows() {
        for (auto& window : m_windows) {
            if (window->m_open) {
                window->Render();
            }
        }
    }
}