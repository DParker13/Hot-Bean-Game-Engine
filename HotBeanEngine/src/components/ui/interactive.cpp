/**
 * @file interactive.cpp
 * @author Daniel Parker (DParker13)
 * @brief Button component
 * @version 0.1
 * @date 2026-03-15
 *
 * @copyright Copyright (c) 2026
 */

#include <HotBeanEngine/components/ui/interactive.hpp>

namespace HBE::Components {
    void Interactive::Deserialize(Core::ISerializationReader &in) {
        in.BeginSection("Interactive");
        in.EndSection();
    }

    void Interactive::Serialize(Core::ISerializationWriter &out) const {
        out.BeginSection("Interactive");
        out.EndSection();
    }

    void Interactive::RenderProperties(int &id) {}
} // namespace HBE::Components