#include "audio_system.hpp"

namespace Systems {
    AudioSystem::AudioSystem(Core::CoreManager& coreManager) {
        coreManager.RegisterSystem<AudioSystem>(this);
        
        coreManager.SetSignature<AudioSystem, Components::Transform>();
    }

    void AudioSystem::LoadMusic(std::string musicFilePath) {
        // load sample.wav in to sample
        _music = Mix_LoadWAV(musicFilePath.data());
        if(!_music) {
            printf("Mix_LoadWAV: %s\n", Mix_GetError());
        }
    }

    void AudioSystem::PlayMusic(int numLoops) {
        if (Mix_Playing(DEFAULT_MUSIC_CHANNEL) == 0) {
            if(Mix_PlayChannel(DEFAULT_MUSIC_CHANNEL, _music, numLoops) == -1) {
                printf("Mix_PlayChannel: %s\n", Mix_GetError());
            }
        }
    }

    void AudioSystem::PlayMusic(int channel, int numLoops) {
        if (Mix_Playing(channel) == 0) {
            if(Mix_PlayChannel(channel, _music, numLoops)==-1) {
                printf("Mix_PlayChannel: %s\n", Mix_GetError());
            }
        }
    }

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

    void AudioSystem::SetVolume(Uint32 volume) {
        
    }

    std::string AudioSystem::ToString() const {
        return "  Audio System Entities: " + std::to_string(_entities.size()) + "\n";
    }
}