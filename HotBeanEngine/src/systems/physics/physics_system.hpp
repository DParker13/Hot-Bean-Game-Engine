#pragma once

#include "../input/input_system.hpp"

using namespace HBE::Components;
using namespace HBE::Application;
using namespace HBE::Core;

namespace Systems {
    class PhysicsSystem : public System {
        private:
            InputSystem& m_input_system;

        public:
            DEFINE_SIGNATURE(PhysicsSystem, Transform2D, RigidBody);
            PhysicsSystem(InputSystem& input_system);

            void OnUpdate() override;
    };
}