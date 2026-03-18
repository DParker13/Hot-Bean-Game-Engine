/**
 * @file ieditor_gui.hpp
 * @brief Interface for editor GUI to decouple editor implementation from core application.
 */
#pragma once

#include <HotBeanEngine/application/listeners/ilog_listener.hpp>
#include <HotBeanEngine/core/igame_loop.hpp>
#include <HotBeanEngine/defaults/components/miscellaneous/camera.hpp>
#include <HotBeanEngine/defaults/components/miscellaneous/transform_2d.hpp>

namespace HBE::Application::GUI {
    /// @brief Abstract interface for editor GUI. Inherits engine game loop hooks and log listening.
    class IEditorGUI : public Core::IGameLoop, public Listeners::ILogListener {
    private:
        Default::Components::Camera m_camera;
        Default::Components::Transform2D m_camera_transform;

    public:
        virtual ~IEditorGUI() = default;

        Default::Components::Camera &GetEditorCamera() { return m_camera; }
        Default::Components::Transform2D &GetEditorCameraTransform() { return m_camera_transform; }
        virtual void InitEditorGUI() = 0;
    };
} // namespace HBE::Application::GUI
