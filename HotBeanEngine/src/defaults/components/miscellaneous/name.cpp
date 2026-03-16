/**
 * @file name.cpp
 * @author Daniel Parker (DParker13)
 * @brief Name component for identifying entities
 * @version 0.1
 * @date 2026-03-15
 *
 * @copyright Copyright (c) 2026
 */

#include <HotBeanEngine/defaults/components/miscellaneous/name.hpp>

#include <HotBeanEngine/editor/property_nodes/string.hpp>

namespace HBE::Default::Components {
    using namespace Application::GUI::PropertyNodes;

    void Name::Serialize(YAML::Emitter &out) const { out << YAML::Key << "name" << YAML::Value << m_name; }

    void Name::Deserialize(YAML::Node &node) {
        if (node["name"]) {
            m_name = node["name"].as<std::string>();
        }
    }

    void Name::RenderProperties(int &id) { String::RenderProperty(id, "Name", m_name, true); }
} // namespace HBE::Default::Components