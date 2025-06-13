#pragma once

#include "../../application/all_application.hpp"

using namespace Core::Components;
using namespace Core::Application;
using namespace Core::ECS;

namespace Core::Systems {
    class PhysicsSystem : public System {
        public:
            PhysicsSystem() = default;

            void SetSignature() override;
            void OnUpdate() override;
    };
}