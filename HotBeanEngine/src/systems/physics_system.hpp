#pragma once

#include "../core/core.hpp"

using namespace Components;
using namespace Core::Application;
using namespace Core::ECS;

namespace Systems {
    class PhysicsSystem : public System {
        public:
            PhysicsSystem();

            //System interface
            void OnUpdate() override;
    };
}