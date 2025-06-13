#pragma once

#include <HotBeanEngine.hpp>

namespace Systems {
    class CustomAudioSystem : public Core::Systems::AudioSystem {
        public:
            CustomAudioSystem() = default;

            void SetSignature() override;
            void OnStart() override;
    };
}