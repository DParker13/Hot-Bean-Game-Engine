/**
 * @file menu.hpp
 * @author Daniel Parker (DParker13)
 * @brief Main menu window for the editor UI.
 * @version 0.1
 * @date 2025-10-17
 *
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <memory>

#include "project_manager.hpp"
#include "windows/new_project_window.hpp"

namespace HBE::Application::GUI {
    /**
     * @class Menu
     * @brief Main menu window for the editor UI.
     *
     * Provides window visibility toggles and menu bar functionality.
     * Displays all available editor windows and allows users to show/hide them.
     */
    class Menu {
    private:
        std::map<std::string, std::shared_ptr<IWindow>> &m_windows;
        std::shared_ptr<ProjectManager> m_project_manager = nullptr;

    public:
        Menu(std::map<std::string, std::shared_ptr<IWindow>> &windows, std::shared_ptr<ProjectManager> project_manager)
            : m_windows(windows), m_project_manager(project_manager) {}
        ~Menu() = default;

        void Render();
    };
} // namespace HBE::Application::GUI