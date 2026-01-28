/**
 * @file ieditor_gui.hpp
 * @brief Interface for editor GUI to decouple editor implementation from core application.
 */
#pragma once

#include <HotBeanEngine/core/igame_loop.hpp>

namespace HBE::Application::GUI {
    /// @brief Abstract interface for editor GUI. Inherits engine game loop hooks.
    struct IEditorGUI : public HBE::Core::IGameLoop {
        virtual ~IEditorGUI() = default;

        virtual void InitEditorGUI() = 0;
    };
} // namespace HBE::Application::GUI
