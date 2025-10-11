/**
 * @file player.hpp
 * @author Daniel Parker (DParker13)
 * @brief Player component. Used to control an entity using user input.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include <HotBeanEngine/core.hpp>

namespace HBE::Default::Components {
    struct Controller : public Component {
        bool controllable = true;

        Controller() = default;

        std::string GetName() const override {
            return "Controller";
        }

        void Serialize(YAML::Emitter& out) const override {
            out << YAML::Key << "controllable" << YAML::Value << controllable;
        }

        void Deserialize(YAML::Node& node) override {
            if (node["controllable"]) {
                controllable = node["controllable"].as<bool>();
            }
        }
    };
}