#pragma once

#include "../core/managers/core_manager.hpp"
#include "../components/transform.hpp"
#include "../components/rigidbody.hpp"

namespace Systems {
    class PhysicsSystem : public System {
        public:
            PhysicsSystem(Core::CoreManager& coreManager);

            //System interface
            void OnUpdate(float deltaTime) override;

            std::string ToString() const;
    };
}