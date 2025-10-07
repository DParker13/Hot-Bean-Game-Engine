#pragma once

#include "../../application/all_application.hpp"

using namespace HBE::Components;
using namespace HBE::Application;
using namespace HBE::Core;

namespace Systems {
    class AudioSystem : public System {
        private:
            MIX_Mixer* m_mixer; // Channel 1
            MIX_Track* m_track_one;

        public:
            DEFINE_SIGNATURE(AudioSystem);
            AudioSystem();
            ~AudioSystem();

            void LoadMusic(std::string music_file_path);
            void PlayMusic(int numLoops);
            void SetVolume(Uint32 volume);
    };
}