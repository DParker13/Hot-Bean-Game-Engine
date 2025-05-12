#include "audio_system.hpp"

namespace Systems {
    AudioSystem::AudioSystem() : System() {
        App::GetInstance().SetupSystem<AudioSystem>(this);
    }

    /**
     * OnInit is called when the system is initialized.
     * It loads a default music sample and starts playing it.
     */
    void AudioSystem::OnStart() {
        LoadMusic("../assets/music/Summer.wav");
        PlayMusic(-1);
    }

    /**
     * Loads a music sample from the given file path.
     *
     * If the load fails, an error message will be printed to the console.
     *
     * @param musicFilePath the path to the music file
     */
    void AudioSystem::LoadMusic(std::string musicFilePath) {
        // load sample.wav in to sample
        _music = Mix_LoadWAV(musicFilePath.data());
        if(!_music) {
            printf("Mix_LoadWAV: %s\n", Mix_GetError());
        }
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
        if (Mix_Playing(DEFAULT_MUSIC_CHANNEL) == 0) {
            if(Mix_PlayChannel(DEFAULT_MUSIC_CHANNEL, _music, numLoops) == -1) {
                printf("Mix_PlayChannel: %s\n", Mix_GetError());
            }
        }
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
        if (Mix_Playing(channel) == 0) {
            if(Mix_PlayChannel(channel, _music, numLoops)==-1) {
                printf("Mix_PlayChannel: %s\n", Mix_GetError());
            }
        }
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
        if (fadeInTime <= 0) {
            PlayMusic(channel, numLoops);
        }
        else if (Mix_Playing(channel) == 0) {
            if(Mix_FadeInChannel(channel, _music, numLoops, fadeInTime) == -1) {
                printf("Mix_FadeInChannel: %s\n", Mix_GetError());
            }
        }
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
        if (fadeInTime <= 0) {
            if (timeLimit <= 0) {
                PlayMusic(channel, numLoops);
            }
            else if (Mix_PlayChannelTimed(channel, _music, numLoops, timeLimit) == -1) {
                printf("Mix_PlayChannelTimed: %s\n", Mix_GetError());
            }
        }
        else {
            if (timeLimit <= 0) {
                PlayMusic(channel, numLoops, fadeInTime);
            }
            else if (Mix_FadeInChannelTimed(channel, _music, numLoops, fadeInTime, timeLimit) == -1) {
                printf("Mix_FadeInChannelTimed: %s\n", Mix_GetError());
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