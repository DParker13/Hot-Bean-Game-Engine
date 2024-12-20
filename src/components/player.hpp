#pragma once

#include "../core/ecs.hpp"

namespace Components {
    struct Player : public IObject {
        bool controllable;

        Player() : controllable(true) {}

        std::string ToString() const override {
            std::stringstream str;
            str << "    Component: Player \n";
            str << "      Controllable: " << controllable << "\n";
            
            return str.str();
        }
    };
}