#include "audio_system.hpp"

namespace Systems {
    /**
     * OnStart is called when the system is initialized.
     * It loads a default music sample and starts playing it.
     */
    void CustomAudioSystem::OnStart() {
        LoadMusic((std::filesystem::current_path() / "assets" / "music" / "Summer.wav").string());
        PlayMusic(-1);
    }

}