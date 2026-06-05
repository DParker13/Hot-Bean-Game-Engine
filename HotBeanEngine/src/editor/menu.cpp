/**
 * @file menu.cpp
 * @author Daniel Parker (DParker13)
 * @brief Implementation of the main menu window for the editor GUI.
 * Provides window visibility toggles and menu bar functionality.
 * @version 0.1
 * @date 2025-10-17
 *
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/defaults/default_scene.hpp>
#include <HotBeanEngine/defaults/default_scene_serializer.hpp>

#include "editor_utils.hpp"
#include "menu.hpp"

namespace HBE::Application::GUI {
    namespace {
        constexpr SDL_DialogFileFilter kSceneFileFilters[] = {
            {"Scene Files", "yaml;yml"},
            {"All Files", "*"},
        };
    } // namespace

    void Menu::Render() {
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("New Project")) {
                    m_windows["New Project"]->m_open = true;
                }
                if (ImGui::MenuItem("Open Project")) {
                    m_project_manager->OpenProject();
                }
                if (ImGui::MenuItem("Exit")) {
                    g_app.m_quit = true;
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Scene")) {
                if (ImGui::MenuItem("New Scene")) {
                    // g_app.NewScene();
                }
                if (ImGui::MenuItem("Save Scene")) {
                    // g_app.SaveScene();
                }
                if (ImGui::MenuItem("Load Scene")) {
                    ShowFileDialog(
                        g_app.GetWindow(), kSceneFileFilters, static_cast<int>(std::size(kSceneFileFilters)),
                        [](std::string_view path) {
                            std::shared_ptr<Core::ISerializer> serializer =
                                std::make_shared<Default::DefaultSceneSerializer>(g_app.GetComponentFactory());
                            std::shared_ptr<Core::Scene> scene =
                                std::make_shared<Default::DefaultScene>("blah", std::string(path), serializer);
                            g_app.GetSceneManager().RegisterScene(scene);
                            g_app.GetSceneManager().LoadScene(scene);
                        });
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Windows")) {
                for (auto &[name, window] : m_windows) {
                    if (window->m_menu_item_visible) {
                        ImGui::Checkbox(window->m_name.c_str(), &window->m_open);
                    }
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }
} // namespace HBE::Application::GUI