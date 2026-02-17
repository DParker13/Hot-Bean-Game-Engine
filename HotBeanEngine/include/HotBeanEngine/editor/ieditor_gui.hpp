/**
 * @file ieditor_gui.hpp
 * @brief Interface for editor GUI to decouple editor implementation from core application.
 */
#pragma once

#include <HotBeanEngine/core/igame_loop.hpp>
#include <HotBeanEngine/defaults/components/miscellaneous/camera.hpp>
#include <HotBeanEngine/defaults/components/miscellaneous/transform_2d.hpp>

namespace HBE::Application::GUI {
    /// @brief Abstract interface for editor GUI. Inherits engine game loop hooks.
    class IEditorGUI : public HBE::Core::IGameLoop {
    private:
        HBE::Default::Components::Camera m_camera;
        HBE::Default::Components::Transform2D m_camera_transform;

    public:
        virtual ~IEditorGUI() = default;

        virtual void InitEditorGUI() = 0;
        virtual HBE::Default::Components::Camera &GetEditorCamera() { return m_camera; }
        virtual HBE::Default::Components::Transform2D &GetEditorCameraTransform() { return m_camera_transform; }
    };
} // namespace HBE::Application::GUI
