#include "audio_system.hpp"

namespace Systems {
    AudioSystem::~AudioSystem() {
        //MIX_FreeChunk(m_music);
    }

    /**
     * Loads a music sample from the given file path.
     *
     * If the load fails, an error message will be printed to the console.
     *
     * @param music_file_path the path to the music file
     */
    void AudioSystem::LoadMusic(std::string music_file_path) {
        // load sample.wav in to sample
        // m_music = MIX_LoadWAV(music_file_path.data());
        // if(!m_music) {
        //     printf("MIX_LoadWAV: %s\n", MIX_GetError());
        // }
    }

    /**
     * Plays the loaded music sample on the default channel.
     *
     * If the music is already playing on the default channel, this function does nothing.
     *
     * If the play fails, an error message will be printed to the console.
     *
     * @param numLoops the number of loops to play. A value of -1 means the music will play
     *                 until stopped manually.
     */
    void AudioSystem::PlayMusic(int numLoops) {
        // if (MIX_Playing(DEFAULT_MUSIC_CHANNEL) == 0) {
        //     if(MIX_PlayChannel(DEFAULT_MUSIC_CHANNEL, m_music, numLoops) == -1) {
        //         printf("MIX_PlayChannel: %s\n", MIX_GetError());
        //     }
        // }
    }

    /**
     * Plays the loaded music sample on the given channel.
     *
     * If the music is already playing on the given channel, this function does nothing.
     *
     * If the play fails, an error message will be printed to the console.
     *
     * @param channel the SDL_mixer channel to play the music on
     * @param numLoops the number of loops to play. A value of -1 means the music will play
     *                 until stopped manually.
     */
    void AudioSystem::PlayMusic(int channel, int numLoops) {
        // if (MIX_Playing(channel) == 0) {
        //     if(MIX_PlayChannel(channel, m_music, numLoops)==-1) {
        //         printf("MIX_PlayChannel: %s\n", MIX_GetError());
        //     }
        // }
    }

    /**
     * Plays the loaded music sample on the given channel with a fade-in effect.
     *
     * If the music is already playing on the given channel, this function does nothing.
     *
     * If the play fails, an error message will be printed to the console.
     *
     * @param channel the SDL_mixer channel to play the music on
     * @param numLoops the number of loops to play. A value of -1 means the music will play
     *                 until stopped manually.
     * @param fadeInTime the time in milliseconds to fade in the music. A value of 0
     *                    disables the fade-in effect.
     */
    void AudioSystem::PlayMusic(int channel, int numLoops, int fadeInTime) {
        // if (fadeInTime <= 0) {
        //     PlayMusic(channel, numLoops);
        // }
        // else if (MIX_Playing(channel) == 0) {
        //     if(MIX_FadeInChannel(channel, m_music, numLoops, fadeInTime) == -1) {
        //         printf("MIX_FadeInChannel: %s\n", MIX_GetError());
        //     }
        // }
    }

    /**
     * Plays the loaded music sample on the given channel with a fade-in effect and a time limit.
     *
     * If the music is already playing on the given channel, this function does nothing.
     *
     * If the play fails, an error message will be printed to the console.
     *
     * @param channel the SDL_mixer channel to play the music on
     * @param numLoops the number of loops to play. A value of -1 means the music will play
     *                 until stopped manually.
     * @param fadeInTime the time in milliseconds to fade in the music. A value of 0
     *                    disables the fade-in effect.
     * @param timeLimit the time in milliseconds to play the music. A value of 0 disables the
     *                  time limit.
     */
    void AudioSystem::PlayMusic(int channel, int numLoops, int fadeInTime, int timeLimit) {
        // if (fadeInTime <= 0) {
        //     if (timeLimit <= 0) {
        //         PlayMusic(channel, numLoops);
        //     }
        //     else if (MIX_PlayChannelTimed(channel, m_music, numLoops, timeLimit) == -1) {
        //         printf("MIX_PlayChannelTimed: %s\n", MIX_GetError());
        //     }
        // }
        // else {
        //     if (timeLimit <= 0) {
        //         PlayMusic(channel, numLoops, fadeInTime);
        //     }
        //     else if (MIX_FadeInChannelTimed(channel, m_music, numLoops, fadeInTime, timeLimit) == -1) {
        //         printf("MIX_FadeInChannelTimed: %s\n", MIX_GetError());
        //     }
        // }
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