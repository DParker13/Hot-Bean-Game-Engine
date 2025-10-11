#pragma once

#include <HotBeanEngine/application/application.hpp>

using namespace HBE::Application;
using namespace HBE::Core;

namespace HBE::Default::Systems {
    class AudioSystem : public System {
        private:
            //MIX_Mixer* m_mixer; // Channel 1
            //MIX_Track* m_track_one;

        public:
            DEFINE_SIGNATURE(AudioSystem);
            AudioSystem();
            ~AudioSystem();

            void LoadMusic(std::string music_file_path);
            void PlayMusic(int numLoops);
            void SetVolume(Uint32 volume);
    };
}