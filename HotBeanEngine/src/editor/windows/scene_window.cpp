/**
 * @file scene_window.cpp
 * @author Daniel Parker (DParker13)
 * @brief Implementation of the scene window for browsing and selecting scenes.
 * Displays scenes and allows you to load and manage them.
 * @version 0.1
 * @date 2026-06-13
 *
 * @copyright Copyright (c) 2026
 */

#include "scene_window.hpp"

#include <HotBeanEngine/application/scene.hpp>
#include <misc/cpp/imgui_stdlib.h>

#include "../editor_utils.hpp"
#include "../project_manager.hpp"

namespace HBE::GUI {
    using namespace Core;

    namespace {
        constexpr SDL_DialogFileFilter kSceneFileFilters[] = {
            {"Scene Files", "yaml;yml"},
            {"All Files", "*"},
        };
    } // namespace

    void SceneWindow::RenderWindow() {
        if (ImGui::Begin(m_name.c_str(), &m_open)) {
            // Should this be cached instead of retrieved every frame? Maybe not a big deal since it's just a pointer
            // comparison.
            std::shared_ptr<IScene> current_scene = g_app.GetSceneManager().GetCurrentScene();
            RenderSceneList(current_scene);

            ImGui::Separator();
            if (ImGui::Button("Add New Scene")) {
                AddScene();
            }
        }
        ImGui::End();
    }

    void SceneWindow::RenderSceneList(std::shared_ptr<IScene> current_scene) {
        ImGui::Text("Scenes:");
        ImGui::Separator();

        for (auto &[name, scene] : g_app.GetSceneManager().m_scenes) {
            ImGui::PushID(name.c_str());
            std::string scene_name = name;
            if (current_scene == scene) {
                scene_name += " (Loaded)";
            }

            ImGui::BeginGroup();
            if (ImGui::CollapsingHeader(scene_name.c_str(), ImGuiTreeNodeFlags_Framed)) {
                std::string path = scene->m_scene_path.string();
                ImGui::Text("Scene Path:");
                ImGui::SameLine();
                if (ImGui::InputText("##Scene Path", &path, ImGuiInputTextFlags_ElideLeft)) {
                    scene->m_scene_path = path;
                }
                ImGui::SameLine();
                if (ImGui::Button("...")) {
                    ShowFileDialog(
                        g_app.GetWindow(), kSceneFileFilters, static_cast<int>(std::size(kSceneFileFilters)),
                        [scene](std::string_view selected_path) { scene->m_scene_path = std::string(selected_path); });
                }
                ImGui::Spacing();
                if (ImGui::Button("Load##")) {
                    g_app.GetSceneManager().LoadScene(scene, true);
                }
                ImGui::SameLine();
                if (ImGui::Button("Delete##")) {
                    if (current_scene == scene) {
                        g_app.GetSceneManager().UnloadScene(false);
                    }
                    g_app.GetSceneManager().UnregisterScene(scene);
                }
            }
            ImGui::EndGroup();
            ImGui::PopID();
        }
    }

    void SceneWindow::AddScene() {
        ShowFileDialog(g_app.GetWindow(), kSceneFileFilters, static_cast<int>(std::size(kSceneFileFilters)),
                       [this](std::string_view selected_path) {
                           std::filesystem::path path(selected_path);
                           std::string name = path.stem().string();
                           auto new_scene = std::make_shared<Application::Scene>(name, path);
                           g_app.GetSceneManager().RegisterScene(new_scene);
                           m_project_manager->SaveProject();
                       });
    }

    void SceneWindow::RemoveScene(std::shared_ptr<IScene> scene) {
        if (g_app.GetSceneManager().GetCurrentScene() == scene) {
            YesNoCancelDialog(g_app.GetWindow(), "Save and Close Scene",
                              "Would you like to save changes before closing?", [scene](int response) {
                                  // 0 = Yes, 1 = No, 2 = Cancel
                                  if (response < 2) {
                                      g_app.GetSceneManager().UnloadScene(response == 0);
                                      g_app.GetSceneManager().UnregisterScene(scene);
                                  }
                              });
        }
        else {
            g_app.GetSceneManager().UnregisterScene(scene);
        }
    }
} // namespace HBE::GUI