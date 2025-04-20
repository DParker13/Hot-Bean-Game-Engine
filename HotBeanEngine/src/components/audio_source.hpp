/**
 * @file audio_source.hpp
 * @author Daniel Parker (DParker13)
 * @brief 
 * @version 0.1
 * @date 2025-04-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "../core/core.hpp"

namespace Components {
    struct AudioSource : public Component {
        /**
         * The path to the audio file.
         */
        std::string path;
        
        AudioSource() {
            Component::_name = "AudioSource";
        }

        std::string ToString() const override {
            std::stringstream str;
            str << "    Component: AudioSource \n";
            str << "      Path: " << path << "\n";
            return str.str();
        }
    };
}