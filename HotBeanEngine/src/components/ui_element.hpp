/**
 * @file ui_element.hpp
 * @author Daniel Parker (DParker13)
 * @brief UI element component. Used for rendering UI elements.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "../core/core.hpp"

#include "enums/ui_type.hpp"

namespace Components {

    struct UIElement : public Component {
        Enums::UIType _type = Enums::UIType::Empty;
        bool _dirty = true;

        UIElement() = default;

        virtual std::string GetName() const override {
            return "UIElement";
        }

        virtual void Serialize(YAML::Emitter& out) const override {
            out << YAML::Key << "type" << YAML::Value << (int)_type;
        }

        virtual void Deserialize(YAML::Node& node) override {
            if (node["type"]) {
                _type = (Enums::UIType)node["type"].as<int>();
            }

            if (node["dirty"]) {
                _dirty = node["dirty"].as<bool>();
            }
        }

        std::string ToString() const override {
            return "UIElement";
        }
    };
}