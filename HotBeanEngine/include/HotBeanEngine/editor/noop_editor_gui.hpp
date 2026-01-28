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
        ~NoopEditorGUI() override = default;

        void InitEditorGUI() override {}

        void OnStart() override {}
        void OnPreEvent() override {}
        void OnEvent(SDL_Event & /*event*/) override {}
        void OnWindowResize(SDL_Event & /*event*/) override {}
        void OnUpdate() override {}
        void OnRender() override {}
        void OnPostRender() override {}
    };
} // namespace HBE::Application::GUI
