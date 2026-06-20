/**
 * @file ieditor_gui.hpp
 * @brief Interface for editor GUI to decouple editor implementation from core application.
 */
#pragma once

#include <HotBeanEngine/application/listeners/ilog_listener.hpp>
#include <HotBeanEngine/components/miscellaneous/camera.hpp>
#include <HotBeanEngine/components/miscellaneous/transform_2d.hpp>
#include <HotBeanEngine/core/igame_loop.hpp>

namespace HBE::GUI {
    /// @brief Abstract interface for editor GUI. Inherits engine game loop hooks and log listening.
    class IEditorGUI : public Core::IGameLoop, public Application::Listeners::ILogListener {
    private:
        Components::Camera m_camera;
        Components::Transform2D m_camera_transform;

    public:
        virtual ~IEditorGUI() = default;

        Components::Camera &GetEditorCamera() { return m_camera; }
        Components::Transform2D &GetEditorCameraTransform() { return m_camera_transform; }
        virtual void InitEditorGUI() = 0;
    };
} // namespace HBE::GUI
