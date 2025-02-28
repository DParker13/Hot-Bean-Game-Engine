#pragma once

#include <SDL_mixer.h>

#include "../core/managers/core_manager.hpp"
#include "../components/transform-2d.hpp"

namespace Systems {
    class AudioSystem : public System {
        private:
            Mix_Chunk* _music; // Channel 1
            const Uint32 DEFAULT_MUSIC_CHANNEL = 1;

        public:
            AudioSystem(Core::CoreManager& coreManager);
            
            //System Interface
            void OnInit() override;

            void LoadMusic(std::string musicFilePath);
            void PlayMusic(int numLoops);
            void PlayMusic(int channel, int numLoops);
            void PlayMusic(int channel, int numLoops, int fadeInTime);
            void PlayMusic(int channel, int numLoops, int fadeInTime, int timeLimit);
            void SetVolume(Uint32 volume);
            std::string ToString() const;
    };
}