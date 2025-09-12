#pragma once

#include "../../application/all_application.hpp"

using namespace HBE::Components;
using namespace HBE::Application;
using namespace HBE::Core;

namespace Systems {
    class AudioSystem : public System {
        private:
            Mix_Chunk* m_music; // Channel 1
            const Uint8 DEFAULT_MUSIC_CHANNEL = 1;

        public:
            DEFINE_SIGNATURE(AudioSystem);
            AudioSystem() = default;
            ~AudioSystem();

            void LoadMusic(std::string music_file_path);
            void PlayMusic(int numLoops);
            void PlayMusic(int channel, int numLoops);
            void PlayMusic(int channel, int numLoops, int fadeInTime);
            void PlayMusic(int channel, int numLoops, int fadeInTime, int timeLimit);
            void SetVolume(Uint32 volume);
    };
}