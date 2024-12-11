#pragma once

#include "../core/ecs.hpp"

namespace Components {
    struct Gravity : public IObject {
        float force;

        Gravity()
        : force(-9.8f) {};

        Gravity(const float force)
        : force(force) {}

        /**
         * Prints the details of the Transform component to the console.
         * The output includes the position, rotation (as a quaternion), 
         * and scale of the component in a formatted string.
         */
        void Print() const override {
            std::string str = "    Component: Gravity \n";
            str += "      Force: " + std::to_string(force) + "\n";
            std::cout << str;
        }
    };
}