#include <HotBeanEngine/defaults/systems/audio/audio_system.hpp>

namespace HBE::Default::Systems {

    AudioSystem::AudioSystem() : System("Audio System") {
        m_mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
        m_track_one = MIX_CreateTrack(m_mixer);
    }

    AudioSystem::~AudioSystem() {
        MIX_DestroyMixer(m_mixer);
    }

    /**
     * Loads a music sample from the given file path.
     * If the load fails, an error message will be printed to the console.
     *
     * @param music_file_path the path to the music file
     */
    void AudioSystem::LoadMusic(std::string music_file_path) {
        // load sample.wav in to sample
        
        MIX_Audio* audio = MIX_LoadAudio(m_mixer, music_file_path.data(), false);
        if(!audio) {
            LOG(LoggingType::ERROR, std::string(SDL_GetError()));
        }

        if (!MIX_SetTrackAudio(m_track_one, audio)) {
            LOG(LoggingType::ERROR, std::string(SDL_GetError()));
        }
    }

    /**
     * Plays the loaded music sample on the track one.
     * If the music is already playing on track one, this function does nothing.
     * If the play fails, an error message will be printed to the console.
     *
     * @param numLoops the number of loops to play. A value of -1 means the music will play
     *                 until stopped manually.
     */
    void AudioSystem::PlayMusic(int numLoops) {
        if (!MIX_TrackPlaying(m_track_one)) {
            if(!MIX_PlayTrack(m_track_one, numLoops)) {
                LOG(LoggingType::ERROR, std::string(SDL_GetError()));
            }
        }
    }

    /**
     * Sets the volume of the music channel to the given value.
     *
     * The volume is given as a Uint32, where 0 is mute and 128 is maximum volume.
     *
     * @param volume the volume value
     */
    void AudioSystem::SetVolume(Uint32 volume) {
        
    }
}