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

namespace HBE::Editor::Managers {
    class ProjectManager {
    private:
        std::vector<std::filesystem::path> m_project_files;

    public:
        Core::Project m_project;

        ProjectManager() = default;
        ~ProjectManager() = default;

        void CreateNewProject(const Core::Project &project);
        void OpenProject();
        void LoadProject(const std::filesystem::path &path);
        void SaveProject();
        std::vector<std::filesystem::path> GetProjectFiles() const { return m_project_files; }

    private:
        void LoadProject();
        void SetupProjectDirectories();
    };
} // namespace HBE::Editor::Managers