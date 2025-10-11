#pragma once

#include <HotBeanEngine/HotBeanEngine_Defaults.hpp>

namespace Systems {
    class CustomAudioSystem : public HBE::Default::Systems::AudioSystem {
    public:
        EXTEND_SYSTEM(AudioSystem, CustomAudioSystem);
        CustomAudioSystem() = default;

        void OnStart() override;
    };
}