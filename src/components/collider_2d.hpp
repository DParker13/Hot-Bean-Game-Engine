/**
 * @file collider_2d.hpp
 * @author Daniel Parker (DParker13)
 * @brief Used for 2D collision detection.
 * @version 0.1
 * @date 2025-03-02
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once

#include <core.hpp>

namespace Components {
    struct Collider2D : public Component {
        glm::vec2 _bounding_box;
        bool _is_static;
        bool _is_trigger;

        Collider2D() = default;

        std::string ToString() const override {
            std::stringstream str;
            str << "    Component: Collider2D \n";
            
            return str.str();
        }
    };
}