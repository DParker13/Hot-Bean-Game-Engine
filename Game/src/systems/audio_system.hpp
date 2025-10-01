#pragma once

#include <HotBeanEngine.hpp>

namespace Systems {
    class CustomAudioSystem : public Systems::AudioSystem {
        public:
            EXTEND_SYSTEM(AudioSystem, CustomAudioSystem);
            CustomAudioSystem() = default;

            void OnStart() override;
    };
}