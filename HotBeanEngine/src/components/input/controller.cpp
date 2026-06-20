/**
 * @file controller.cpp
 * @author Daniel Parker (DParker13)
 * @brief Controller component. Used to control an entity using user input.
 * @version 0.1
 * @date 2026-03-15
 *
 * @copyright Copyright (c) 2026
 */

#include <HotBeanEngine/components/input/controller.hpp>

namespace HBE::Components {
    void Controller::Serialize(Core::IComponentWriter &out) const { out.Write("controllable", controllable); }

    void Controller::Deserialize(Core::IComponentReader &in) {
        if (in.Has("controllable")) {
            controllable = in.ReadBool("controllable");
        }
    }

    void Controller::RenderProperties(int &id) {
        GUI::PropertyNodes::Bool::RenderProperty(id, "Controllable", controllable);
    }
} // namespace HBE::Components