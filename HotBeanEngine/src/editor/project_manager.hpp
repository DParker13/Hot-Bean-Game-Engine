/**
 * @file project_manager.hpp
 * @author Daniel Parker (DParker13)
 * @brief Manages project creation, loading, and saving.
 * @version 0.1
 * @date 2026-04-12
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <HotBeanEngine/core/project.hpp>

namespace HBE::Application::GUI {
    class ProjectManager {
    public:
        Core::Project m_project;

        ProjectManager();
        ~ProjectManager() = default;

        void CreateNewProject(const Core::Project &project);
        void OpenProject();
        int SaveProject();

    private:
        void LoadProject(const std::filesystem::path &path);
        void LoadProject();
        void SetupProjectDirectories();
    };
} // namespace HBE::Application::GUI