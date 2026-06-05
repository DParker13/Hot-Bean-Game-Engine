/**
 * @file property_window.hpp
 * @author Daniel Parker (DParker13)
 * @brief Window for editing entity component properties.
 * @version 0.1
 * @date 2025-10-30
 *
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <functional>
#include <imgui.h>

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/editor/iproperty_renderable.hpp>
#include <HotBeanEngine/editor/iwindow.hpp>

namespace HBE::Application::GUI {
    /**
     * @class PropertyWindow
     * @brief Window for editing entity component properties.
     *
     * Displays and manages component properties with collapsible sections.
     * Allows users to inspect and modify properties of selected entities.
     */
    class PropertyWindow : public IWindow {
    private:
        std::vector<std::pair<std::string, IPropertyRenderable *>> m_properties;

    public:
        PropertyWindow() : IWindow("Properties") {}
        ~PropertyWindow() = default;

        void RenderWindow() override;
        void SetProperties(std::vector<std::pair<std::string, IPropertyRenderable *>> properties);
    };
} // namespace HBE::Application::GUI