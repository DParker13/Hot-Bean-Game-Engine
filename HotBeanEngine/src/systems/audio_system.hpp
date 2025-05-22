#pragma once

#include <SDL_mixer.h>

#include "../core/core.hpp"

using namespace Core::ECS;
using namespace Core::Application;
using namespace Components;

namespace Systems {
    class AudioSystem : public System {
        private:
            Mix_Chunk* m_music; // Channel 1
            const Uint8 DEFAULT_MUSIC_CHANNEL = 1;

        public:
            AudioSystem() = default;
            ~AudioSystem();

            void SetSignature() override;

            void LoadMusic(std::string music_file_path);
            void PlayMusic(int numLoops);
            void PlayMusic(int channel, int numLoops);
            void PlayMusic(int channel, int numLoops, int fadeInTime);
            void PlayMusic(int channel, int numLoops, int fadeInTime, int timeLimit);
            void SetVolume(Uint32 volume);
    };
}