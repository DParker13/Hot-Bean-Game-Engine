/**
 * @file name.cpp
 * @author Daniel Parker (DParker13)
 * @brief Name component for identifying entities
 * @version 0.1
 * @date 2026-03-15
 *
 * @copyright Copyright (c) 2026
 */

#include <HotBeanEngine/components/miscellaneous/name.hpp>

#include <HotBeanEngine/editor/property_nodes/string.hpp>

namespace HBE::Components {
    using namespace GUI::PropertyNodes;

    void Name::Serialize(Core::ISerializationWriter &out) const { out.Write("name", m_name); }

    void Name::Deserialize(Core::ISerializationReader &in) { in.Read("name", m_name); }

    void Name::RenderProperties(int &id) { String::RenderProperty(id, "Name", m_name, true); }
} // namespace HBE::Components