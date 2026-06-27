/**
 * @file scene_window.hpp
 * @author Daniel Parker (DParker13)
 * @brief Window for browsing and selecting entities.
 * @version 0.1
 * @date 2026-06-13
 *
 * @copyright Copyright (c) 2026
 */
#pragma once

#include <HotBeanEngine/application/application.hpp>
#include <imgui.h>

#include "property_window.hpp"

namespace HBE::GUI {
    class ProjectManager;

    /**
     * @class SceneWindow
     * @brief Window for browsing and selecting scenes.
     *
     * Displays scenes and allows you to load and manage them.
     */
    class SceneWindow : public IWindow {
    private:
        std::shared_ptr<ProjectManager> m_project_manager;

    public:
        SceneWindow(std::shared_ptr<ProjectManager> project_manager)
            : IWindow("Scenes"), m_project_manager(project_manager) {}
        ~SceneWindow() = default;

        virtual void RenderWindow() override;

        void AddScene();
        void RemoveScene(std::shared_ptr<Core::IScene> scene);

    private:
        void RenderSceneList(std::shared_ptr<Core::IScene> current_scene);
    };
} // namespace HBE::GUI