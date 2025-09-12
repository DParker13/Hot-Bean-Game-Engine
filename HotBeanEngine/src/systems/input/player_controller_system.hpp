#pragma once

#include "input_system.hpp"

using namespace HBE::Components;
using namespace HBE::Application;
using namespace HBE::Core;

namespace Systems {
    class PlayerControllerSystem : public System {
        private:
            InputSystem& m_input_system;

        public:
            DEFINE_SIGNATURE(PlayerControllerSystem, Transform2D, Controller);
            PlayerControllerSystem(InputSystem& input_system) : m_input_system(input_system) {}

            void OnUpdate() override;

            void Move(Entity entity, float speed);
    };
}