/**
 * @file gui_manager.hpp
 * @author Daniel Parker (DParker13)
 * @brief Manages the creation and destruction of GUI elements.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <imgui.h>
#include <imgui_internal.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>

#include <HotBeanEngine/core/all_core.hpp>
#include <HotBeanEngine/editor_gui/iwindow.hpp>

namespace HBE::Application::GUI {
    /**
     * @brief Manages ImGui-based editor interface
     * 
     * Handles editor windows, docking layout, and GUI rendering.
     * Provides development tools and runtime inspection.
     */
    class EditorGUI : public HBE::Core::IGameLoop {
    private:
        std::vector<std::shared_ptr<IWindow>> m_windows;

    public:
        EditorGUI();
        ~EditorGUI();
        
        virtual void OnStart() {};
        virtual void OnPreEvent() {};
        virtual void OnEvent(SDL_Event& event);
        virtual void OnWindowResize(SDL_Event& event);
        virtual void OnUpdate() {};
        virtual void OnRender();
        virtual void OnPostRender() {};

    protected:
        virtual void RenderWindows();
        virtual void SetupDefaultDockingLayout();
    };
}