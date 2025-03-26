/**
 * @file audio_source.hpp
 * @author Daniel Parker (DParker13)
 * @brief Audio source component.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include <core.hpp>

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