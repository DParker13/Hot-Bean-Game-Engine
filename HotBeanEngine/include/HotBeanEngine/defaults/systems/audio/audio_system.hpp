/**
 * @file audio_system.hpp
 * @author Daniel Parker (DParker13)
 * @brief Audio system for playing audio files.
 * @version 0.1
 * @date 2025-03-02
 * 
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <HotBeanEngine/application/application.hpp>

namespace HBE::Default::Systems {
    using namespace HBE::Core;
    
    /**
     * @brief Manages audio playback for entities
     */
    class AudioSystem : public ISystem {
        private:
            MIX_Mixer* m_mixer;
            MIX_Track* m_track_one;

        public:
            DEFINE_SIGNATURE(AudioSystem, "Audio System");
            AudioSystem();
            ~AudioSystem();

            void LoadMusic(std::string music_file_path);
            void PlayMusic(int numLoops);
            void SetVolume(Uint32 volume);
    };
}