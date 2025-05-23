#pragma once

#include "../core/core.hpp"

using namespace Components;
using namespace Core::Application;
using namespace Core::ECS;

namespace Systems {
    class PhysicsSystem : public System {
        public:
            PhysicsSystem() = default;

            void SetSignature() override;
            void OnUpdate() override;
    };
}