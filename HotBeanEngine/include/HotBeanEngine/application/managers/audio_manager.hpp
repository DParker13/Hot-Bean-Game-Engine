#pragma once

#include "SDL3_mixer/SDL_mixer.h"
#include <string>

namespace HBE::Application::Managers {
    /**
     * @class AudioManager
     * @brief Manages audio resources and playback for the application.
     *
     * The AudioManager is responsible for loading audio files, managing audio tracks, and controlling playback and
     * volume.
     */
    class AudioManager {
    private:
        MIX_Mixer *m_mixer;
        MIX_Track *m_track_one;

    public:
        AudioManager();
        ~AudioManager();

        void LoadMusic(std::string music_file_path);
        void PlayMusic(int numLoops);
        void SetVolume(Uint32 volume);
    };
} // namespace HBE::Application::Managers