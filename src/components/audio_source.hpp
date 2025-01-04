#pragma once

#include "../core/ecs.hpp"

namespace Components {
    struct AudioSource : public Object {
        AudioSource() {}

        std::string ToString() const override {
            std::stringstream str;
            str << "    Component: Audio Source \n";
            
            return str.str();
        }
    };
}