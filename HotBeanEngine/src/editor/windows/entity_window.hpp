/**
 * @file entity_window.hpp
 * @author Daniel Parker (DParker13)
 * @brief Window for browsing and selecting entities.
 * @version 0.1
 * @date 2025-10-30
 *
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <HotBeanEngine/application/application.hpp>
#include <imgui.h>

#include "property_window.hpp"

namespace HBE::Application::GUI {
    /**
     * @class EntityWindow
     * @brief Window for browsing and selecting entities.
     *
     * Displays entities organized by their systems.
     * Allows users to select entities and view/edit their component properties.
     */
    class EntityWindow : public IWindow {
    private:
        std::shared_ptr<PropertyWindow> m_property_window = nullptr;

    public:
        EntityWindow(std::shared_ptr<PropertyWindow> property_window)
            : IWindow("Entities"), m_property_window(property_window) {}
        ~EntityWindow() = default;

        virtual void RenderWindow() override;
        void EntitySelected(EntityID entity);
    };
} // namespace HBE::Application::GUI