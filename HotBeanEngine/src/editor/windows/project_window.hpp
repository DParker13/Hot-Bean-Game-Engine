/**
 * @file new_project_window.hpp
 * @author Daniel Parker (DParker13)
 * @brief Window for creating a new project.
 * @version 0.1
 * @date 2026-04-13
 *
 * @copyright Copyright (c) 2026
 */
#pragma once

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/editor/iwindow.hpp>

#include "../project_manager.hpp"

namespace HBE::Application::GUI {
    /**
     * @class ProjectWindow
     * @brief Window for managing a project's settings and properties.
     *
     * Provides a user interface for specifying project details and managing an existing project.
     */
    class ProjectWindow : public IWindow {
    private:
        std::shared_ptr<ProjectManager> m_project_manager = nullptr;
        Core::Project m_project;
        bool m_was_opened = false;

    public:
        ProjectWindow(std::shared_ptr<ProjectManager> project_manager)
            : IWindow("Project", false, true), m_project_manager(project_manager), m_project() {}
        ~ProjectWindow() = default;

        void RenderWindow() override;
    };
} // namespace HBE::Application::GUI