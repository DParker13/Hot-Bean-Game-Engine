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
    void Controller::Serialize(Core::ISerializationWriter &out) const {
        out.BeginSection("Controller");
        if (controllable) {
            out.Write("controllable", controllable);
        }
        out.EndSection();
    }

    void Controller::Deserialize(Core::ISerializationReader &in) {
        in.BeginSection("Controller");
        in.Read("controllable", controllable);
        in.EndSection();
    }

    void Controller::RenderProperties(int &id) {
        Editor::PropertyNodes::Bool::RenderProperty(id, "Controllable", controllable);
    }
} // namespace HBE::Components