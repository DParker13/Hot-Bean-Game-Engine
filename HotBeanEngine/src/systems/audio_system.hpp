#pragma once

#include <SDL_mixer.h>

#include "../core/core.hpp"

#include "../components/transform_2d.hpp"

using namespace Core::ECS;
using namespace Core::Application;
using namespace Components;

namespace Systems {
    class AudioSystem : public System {
        private:
            Mix_Chunk* _music; // Channel 1
            const Uint32 DEFAULT_MUSIC_CHANNEL = 1;

        public:
            AudioSystem();
            
            //System Interface
            void OnStart() override;

            void LoadMusic(std::string musicFilePath);
            void PlayMusic(int numLoops);
            void PlayMusic(int channel, int numLoops);
            void PlayMusic(int channel, int numLoops, int fadeInTime);
            void PlayMusic(int channel, int numLoops, int fadeInTime, int timeLimit);
            void SetVolume(Uint32 volume);
            std::string ToString() const;
    };
}