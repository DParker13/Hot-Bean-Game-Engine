#include "audio_system.hpp"

namespace Systems {
    void CustomAudioSystem::SetSignature() {
        EXTEND_SYSTEM(AudioSystem, CustomAudioSystem);
    }

    /**
     * OnStart is called when the system is initialized.
     * It loads a default music sample and starts playing it.
     */
    void CustomAudioSystem::OnStart() {
        LoadMusic("../assets/music/Summer.wav");
        PlayMusic(-1);
    }

}