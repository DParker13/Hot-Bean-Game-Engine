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
#include <HotBeanEngine/editor/property_nodes/string.hpp>

namespace HBE::Default::Components {
    /**
     * @brief Name component for identifying entities
     * Stores a human-readable name for an entity.
     */
    struct Name : public HBE::Core::IComponent, public HBE::Application::GUI::IPropertyRenderable {
        std::string m_name = "";

        DEFINE_NAME("Name");
        Name() = default;

        void Serialize(YAML::Emitter &out) const override { out << YAML::Key << "name" << YAML::Value << m_name; }

        void Deserialize(YAML::Node &node) override {
            if (node["name"]) {
                m_name = node["name"].as<std::string>();
            }
        }

        void RenderProperties(int &id) override { HBE::Application::GUI::PropertyNodes::String::RenderProperty(id, "Name", m_name, true); }
    };
} // namespace HBE::Default::Components