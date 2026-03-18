/**
 * @file noop_editor_gui.hpp
 * @brief No-op editor GUI implementation used for runtime/no-editor builds and tests.
 */
#pragma once

#include <HotBeanEngine/editor/ieditor_gui.hpp>

namespace HBE::Application::GUI {
    class NoopEditorGUI : public IEditorGUI {
    public:
        NoopEditorGUI() = default;
        ~NoopEditorGUI() = default;

        void InitEditorGUI() {}
        void OnLog(Core::LoggingType /*level*/, std::string_view /*message*/) {}

        void OnStart() {}
        void OnPreEvent() {}
        void OnEvent(SDL_Event & /*event*/) {}
        void OnWindowResize(SDL_Event & /*event*/) {}
        void OnUpdate() {}
        void OnRender() {}
        void OnPostRender() {}
    };
} // namespace HBE::Application::GUI
