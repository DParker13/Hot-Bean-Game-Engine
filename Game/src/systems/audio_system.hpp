/**
 * @file audio_system.hpp
 * @author Daniel Parker (DParker13)
 * @brief Custom audio system extending the default audio functionality.
 * @version 0.1
 * @date 2025-05-22
 *
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <HotBeanEngine/HotBeanEngine_Defaults.hpp>

namespace Systems {
    /**
     * @class CustomAudioSystem
     * @brief Custom audio system for the example game.
     * 
     * Extends the default AudioSystem with game-specific initialization.
     * Loads and manages background music and sound effects for the game.
     */
    class CustomAudioSystem : public HBE::Default::Systems::AudioSystem {
    public:
        EXTEND_SYSTEM(AudioSystem, CustomAudioSystem, "Custom Audio System");
        CustomAudioSystem() = default;
        ~CustomAudioSystem() = default;

        void OnStart() override;
    };
} // namespace Systems