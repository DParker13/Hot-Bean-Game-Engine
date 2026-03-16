/**
 * @file controller.cpp
 * @author Daniel Parker (DParker13)
 * @brief Controller component. Used to control an entity using user input.
 * @version 0.1
 * @date 2026-03-15
 *
 * @copyright Copyright (c) 2026
 */

#include <HotBeanEngine/defaults/components/input/controller.hpp>

namespace HBE::Default::Components {
    void Controller::Serialize(YAML::Emitter &out) const {
        out << YAML::Key << "controllable" << YAML::Value << controllable;
    }

    void Controller::Deserialize(YAML::Node &node) {
        if (node["controllable"]) {
            controllable = node["controllable"].as<bool>();
        }
    }

    void Controller::RenderProperties(int &id) {
        Application::GUI::PropertyNodes::Bool::RenderProperty(id, "Controllable", controllable);
    }
} // namespace HBE::Default::Components