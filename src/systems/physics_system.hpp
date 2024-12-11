#pragma once

#include <iostream>

#include "../core/ecs.hpp"
#include "../core/core_manager.hpp"
#include "../components/transform.hpp"
#include "../components/gravity.hpp"
#include "../components/rigidbody.hpp"

namespace Systems {
    class PhysicsSystem : public System {
        public:
            void Update(Core::CoreManager& coreManager, float dt);
            void Print() const;
    };
}