/**
 * @file controller.hpp
 * @author Daniel Parker (DParker13)
 * @brief Controller component. Used to control an entity using user input.
 * @version 0.1
 * @date 2025-02-23
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <HotBeanEngine/core/all_core.hpp>
#include <HotBeanEngine/editor/iproperty_renderable.hpp>
#include <HotBeanEngine/editor/property_nodes/bool.hpp>

namespace HBE::Default::Components {
    /**
     * @brief Input controller component for player input handling
     *
     * Maps input actions to entity behavior.
     * Supports keyboard, mouse, and gamepad input.
     */
    struct Controller : public Core::IComponent, public Application::GUI::IPropertyRenderable {
        bool controllable = true;

        DEFINE_NAME("Controller");
        Controller() = default;

        void Serialize(YAML::Emitter &out) const override;
        void Deserialize(YAML::Node &node) override;
        void RenderProperties(int &id);
    };
} // namespace HBE::Default::Components