/**
 * @file name.hpp
 * @author Daniel Parker (DParker13)
 * @brief Name component for identifying entities
 * @version 0.1
 * @date 2025-12-19
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <HotBeanEngine/core/all_core.hpp>
#include <HotBeanEngine/editor/iproperty_renderable.hpp>

namespace HBE::Default::Components {
    /**
     * @brief Name component for identifying entities
     * Stores a human-readable name for an entity.
     */
    struct Name : public Core::IComponent, public Application::GUI::IPropertyRenderable {
        std::string m_name = "";

        DEFINE_NAME("Name");
        Name() = default;

        void Serialize(YAML::Emitter &out) const override;
        void Deserialize(YAML::Node &node) override;
        void RenderProperties(int &id);
    };
} // namespace HBE::Default::Components