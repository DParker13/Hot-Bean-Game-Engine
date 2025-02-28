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

#include "../core/ecs.hpp"

namespace Components {
    struct Controller : public Component {
        bool controllable = true;

        Controller() {}

        std::string ToString() const override {
            std::stringstream str;
            str << "    Component: Controller \n";
            str << "      Controllable: " << controllable << "\n";
            
            return str.str();
        }
    };
}