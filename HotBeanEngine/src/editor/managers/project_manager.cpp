/**
 * @file project_manager.cpp
 * @author Daniel Parker (DParker13)
 * @brief Manages project creation, loading, and saving for the editor. Handles project file parsing and serialization.
 * @version 0.1
 * @date 2026-06-20
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <cctype>
#include <yaml-cpp/yaml.h>

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/application/scene.hpp>

#include "../editor_utils.hpp"
#include "project_manager.hpp"

namespace HBE::Editor::Managers {
    namespace {
        constexpr SDL_DialogFileFilter kProjectFileFilters[] = {
            {"Project Files", "yaml;yml"},
            {"All Files", "*"},
        };
    } // namespace

    using namespace Core;

    /**
     * @brief Create a new project at the specified path. This is called after the user selects a path in the new
     * project dialog.
     */
    void ProjectManager::CreateNewProject(const Project &project) {
        LOG(LoggingType::INFO, "Creating new project at path: " + (project.m_directory / project.m_file_name).string());
        m_project = project;

        SetupProjectDirectories();
        SaveProject();

        // Update startup project path with newly created project
        g_config.SetStartupProjectPath((m_project.m_directory / m_project.m_file_name).string());
        g_app.SaveConfig();
    }

    /**
     * @brief Set up the standard project directory structure under the main project path. This includes creating an
     * "assets" directory with subdirectories for fonts, music, and sprites.
     */
    void ProjectManager::SetupProjectDirectories() {
        LOG(LoggingType::DEBUG, "Setting up project directories under: " + m_project.m_directory.string());
        std::filesystem::create_directories(m_project.m_directory / "assets" / "fonts");
        std::filesystem::create_directories(m_project.m_directory / "assets" / "music");
        std::filesystem::create_directories(m_project.m_directory / "assets" / "sprites");
    }

    /**
     * @brief Open an existing project by prompting the user to select a project file, then loading the selected project
     * data and state.
     */
    void ProjectManager::LoadProject() {
        if (!m_project.m_name.empty() && !m_project.m_directory.empty()) {
            LoadProject(m_project.m_directory / m_project.m_file_name);
        }
        else {
            LOG(LoggingType::ERROR, "Failed to load project from existing instance");
        }
    }

    /**
     * @brief Open an existing project by prompting the user to select a project file, then loading the selected project
     * data and state.
     */
    void ProjectManager::LoadProject(std::filesystem::path const &path) {
        LOG(LoggingType::DEBUG, "Loading project: " + path.string());
        try {
            std::shared_ptr<Core::ISerializer> serializer =
                g_app.GetSerializationManager().GetSerializer("BasicSerializer");
            serializer->Deserialize(path, m_project);

            // Scenes (list of scene yaml paths)
            // TODO: This should work with all serializers
            if (m_project.m_scenes.size() > 0) {
                // Register scenes in the application's scene manager
                bool first_scene_loaded = false;
                for (const auto &scene_path : m_project.m_scenes) {

                    if (!std::filesystem::exists(scene_path) || !std::filesystem::is_regular_file(scene_path)) {
                        LOG(LoggingType::WARNING,
                            "Skipping invalid scene entry in project file: " + scene_path.string());
                        continue;
                    }

                    std::shared_ptr<IScene> scene = std::make_shared<Application::Scene>();

                    serializer->Deserialize(scene_path, *scene);

                    if (!scene->m_name.empty() && !scene_path.empty()) {
                        g_app.GetSceneManager().RegisterScene(scene);

                        // Load the first scene immediately after registration to set it as the active scene
                        if (!first_scene_loaded) {
                            g_app.GetSceneManager().LoadScene(scene);
                            first_scene_loaded = true;
                        }
                    }
                }
            }

            // Update startup project path with newly loaded project
            g_config.SetStartupProjectPath(path);
            g_app.SaveConfig();

            LOG(LoggingType::INFO,
                "Successfully loaded project: " + m_project.m_name + "(" + m_project.m_directory.string() + ")");
        } catch (YAML::Exception &) {
            LOG(LoggingType::ERROR,
                "Failed to load project: " + m_project.m_name + "(" + m_project.m_directory.string() + ")");
        }
    }

    void ProjectManager::OpenProject() {
        ShowFileDialog(g_app.GetWindow(), kProjectFileFilters, static_cast<int>(std::size(kProjectFileFilters)),
                       [this](std::string_view path) { LoadProject(path); });
    }

    /**
     * @brief Save the current project data and state to the project file path.
     * @return int 0 on success, -1 on failure.
     */
    void ProjectManager::SaveProject() {
        auto project_serializer = g_app.GetSerializationManager().GetSerializer("BasicSerializer");
        project_serializer->Serialize(m_project.m_directory / m_project.m_file_name, m_project);
    }

    std::string MakeProjectFileName(std::string_view name) {
        std::string fileName;
        fileName.reserve(name.size());

        bool lastWasUnderscore = true; // Prevent leading underscore.
        for (unsigned char ch : name) {
            if (std::isalnum(ch)) {
                fileName.push_back(static_cast<char>(std::tolower(ch)));
                lastWasUnderscore = false;
            }

            else if (std::isspace(ch) || ch == '-' || ch == '_') {
                if (lastWasUnderscore) {
                    continue;
                }

                fileName.push_back('_');
                lastWasUnderscore = true;
            }
        }

        // Remove trailing underscore if input ended with separators.
        if (!fileName.empty() && fileName.back() == '_') {
            fileName.pop_back();
        }

        if (fileName.empty()) {
            fileName = "project";
        }

        return fileName + ".yaml";
    }
} // namespace HBE::Editor::Managers