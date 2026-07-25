/**
 * @file project_window.hpp
 * @author Daniel Parker (DParker13)
 * @brief Window for managing a project's settings and properties.
 * @version 0.1
 * @date 2026-04-13
 *
 * @copyright Copyright (c) 2026
 */
#pragma once

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/editor/iwindow.hpp>

#include "../managers/project_manager.hpp"

namespace HBE::Editor {
    /**
     * @class ProjectWindow
     * @brief Window for managing a project's settings and properties.
     *
     * Provides a user interface for specifying project details and managing an existing project.
     */
    class ProjectWindow : public IWindow {
    private:
        std::shared_ptr<Managers::ProjectManager> m_project_manager = nullptr;
        Core::Project m_project;
        bool m_was_opened = false;

    public:
        ProjectWindow(std::shared_ptr<Managers::ProjectManager> project_manager)
            : IWindow("Project", false, true), m_project_manager(project_manager), m_project() {}
        ~ProjectWindow() = default;

        void RenderWindow() override;
    };
} // namespace HBE::Editor