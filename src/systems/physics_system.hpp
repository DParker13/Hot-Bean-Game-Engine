#pragma once

#include "../managers/core_manager.hpp"
#include "../components/transform.hpp"
#include "../components/rigidbody.hpp"

namespace Systems {
    class PhysicsSystem : public System {
        public:
            PhysicsSystem() = default;
            PhysicsSystem(Core::CoreManager& coreManager);
            void Update(Core::CoreManager& coreManager, float dt);
            std::string ToString() const;
    };
}