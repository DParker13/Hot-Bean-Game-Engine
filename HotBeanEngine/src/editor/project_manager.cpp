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

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/application/scene.hpp>

#include "editor_utils.hpp"
#include "project_manager.hpp"

#include <cctype>

namespace HBE::GUI {
    namespace {
        constexpr SDL_DialogFileFilter kProjectFileFilters[] = {
            {"Project Files", "yaml;yml"},
            {"All Files", "*"},
        };
    } // namespace

    using namespace Core;

    ProjectManager::ProjectManager() : m_project(Project()) {
        if (!STARTUP_PROJECT_PATH.empty()) {
            LoadProject(STARTUP_PROJECT_PATH);
        }
    }

    /**
     * @brief Create a new project at the specified path. This is called after the user selects a path in the new
     * project dialog.
     */
    void ProjectManager::CreateNewProject(const Project &project) {
        LOG(LoggingType::INFO, "Creating new project at path: " + project.GetFullPath().string());
        m_project = project;

        SetupProjectDirectories();
        SaveProject();

        // Update startup project path with newly created project
        STARTUP_PROJECT_PATH = m_project.GetFullPath();
        SaveConfig();
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
            LoadProject(m_project.GetFullPath());
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
            YAML::Node config = YAML::LoadFile(path.string());

            // Project
            if (config["Project"]["name"]) {
                m_project.m_name = config["Project"]["name"].as<std::string>();
            }
            if (config["Project"]["version"]) {
                m_project.m_version = config["Project"]["version"].as<float>();
            }
            if (config["Project"]["file"]) {
                m_project.m_file = config["Project"]["file"].as<std::string>();
            }
            if (config["Project"]["directory"]) {
                m_project.m_directory = config["Project"]["directory"].as<std::string>();
            }

            // Scenes (list of scene yaml paths)
            // TODO: This should work with all serializers
            if (config["Scenes"]) {
                // Register scenes in the application's scene manager
                for (const auto &scene_file_node : config["Scenes"]) {
                    std::string scene_path = scene_file_node["path"].as<std::string>();

                    if (scene_path.empty()) {
                        LOG(LoggingType::WARNING, "Skipping invalid scene entry in project file with empty path");
                        continue;
                    }

                    try {
                        YAML::Node scene_node = YAML::LoadFile(scene_path);

                        if (!scene_node["Scene"] || !scene_node["Scene"]["name"]) {
                            LOG(LoggingType::WARNING, "Skipping invalid scene entry in project file: " + scene_path);
                            continue;
                        }

                        std::string scene_name = "";
                        if (scene_node["Scene"]["name"]) {
                            scene_name = scene_node["Scene"]["name"].as<std::string>();
                        }

                        if (!scene_name.empty() && !scene_path.empty()) {
                            std::shared_ptr<IScene> scene =
                                std::make_shared<Application::Scene>(scene_name, scene_path);
                            g_app.GetSceneManager().RegisterScene(scene);
                        }
                    } catch (const YAML::Exception &e) {
                        LOG(LoggingType::ERROR,
                            "Failed to load scene file: " + scene_path + " with error: " + std::string(e.what()));
                        continue;
                    }
                }
            }

            // Update startup project path with newly loaded project
            STARTUP_PROJECT_PATH = m_project.GetFullPath();
            SaveConfig();

            LOG(LoggingType::INFO,
                "Successfully loaded project: " + m_project.m_name + "(" + m_project.GetFullPath().string() + ")");
        } catch (YAML::Exception &) {
            LOG(LoggingType::ERROR,
                "Failed to load project: " + m_project.m_name + "(" + m_project.GetFullPath().string() + ")");
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
    int ProjectManager::SaveProject() {
        try {
            LOG(LoggingType::DEBUG, "Saving project to: " + m_project.GetFullPath().string());
            YAML::Emitter out;
            out.SetIndent(2);

            out << YAML::BeginMap;

            // Project
            out << YAML::Key << "Project" << YAML::Value;
            out << YAML::BeginMap;
            out << YAML::Key << "name" << YAML::Value << YAML::DoubleQuoted << m_project.m_name;
            out << YAML::Key << "version" << YAML::Value << m_project.m_version;
            out << YAML::Key << "file" << YAML::Value << m_project.m_file;
            out << YAML::Key << "directory" << YAML::Value << m_project.m_directory.string();
            out << YAML::EndMap;

            // Scenes
            out << YAML::Key << "Scenes" << YAML::Value;
            out << YAML::BeginSeq;
            for (const auto [name, scene] : g_app.GetSceneManager().m_scenes) {
                out << YAML::BeginMap;
                out << YAML::Key << "path" << YAML::Value << scene->m_scene_path.string();
                out << YAML::EndMap;
            }
            out << YAML::EndSeq;

            out << YAML::EndMap;

            std::ofstream file{m_project.GetFullPath().string()};

            if (!file.is_open()) {
                LOG(LoggingType::ERROR, "Failed to open project file for write: " + m_project.GetFullPath().string());
                return -1;
            }

            file << out.c_str() << "\n";
            LOG(LoggingType::INFO, "Project saved successfully: " + m_project.GetFullPath().string());

            return 0;
        } catch (const std::exception &ex) {
            LOG(LoggingType::ERROR, "Exception while saving project: " + std::string(ex.what()));
            return -1;
        } catch (...) {
            LOG(LoggingType::ERROR, "Unknown exception while saving project.");
            return -1;
        }
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
} // namespace HBE::GUI