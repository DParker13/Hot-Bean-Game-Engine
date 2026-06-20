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

namespace HBE::GUI {
    /**
     * @class NewProjectWindow
     * @brief Window for creating a new project.
     *
     * Provides a user interface for specifying project details and creating a new project.
     */
    class NewProjectWindow : public IWindow {
    private:
        std::shared_ptr<ProjectManager> m_project_manager = nullptr;
        Core::Project m_new_project;

    public:
        NewProjectWindow(std::shared_ptr<ProjectManager> project_manager)
            : IWindow("New Project", false, false), m_project_manager(project_manager), m_new_project() {}
        ~NewProjectWindow() = default;

        void RenderWindow() override;
    };
} // namespace HBE::GUI