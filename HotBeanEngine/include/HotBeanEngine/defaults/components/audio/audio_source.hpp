/**
 * @file audio_source.hpp
 * @author Daniel Parker (DParker13)
 * @brief Audio Source component. Used to play audio files.
 * @version 0.1
 * @date 2025-04-16
 * 
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <HotBeanEngine/core/all_core.hpp>

namespace HBE::Default::Components {
    using namespace HBE::Core;
    
    /**
     * @brief Audio source component for sound playback
     * 
     * Manages audio clip playback and volume control.
     * Integrates with SDL_mixer for audio output.
     */
    struct AudioSource : public IComponent {
        /**
         * The path to the audio file.
         */
        std::string path;

        DEFINE_NAME("AudioSource");
        AudioSource() = default;

        void Serialize(YAML::Emitter& out) const override {
            out << YAML::Key << "path" << YAML::Value << path;
        }

        void Deserialize(YAML::Node& node) override {
            path = node["path"].as<std::string>();
        }
    };
}