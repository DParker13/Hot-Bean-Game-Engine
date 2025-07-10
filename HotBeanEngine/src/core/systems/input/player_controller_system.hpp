#pragma once

#include "input_system.hpp"

using namespace Core::Components;
using namespace Core::Application;
using namespace Core::ECS;

namespace Core::Systems {
    class PlayerControllerSystem : public System {
        public:
            PlayerControllerSystem(InputSystem& input_system) : m_input_system(input_system) {}

            void SetSignature() override;
            void OnUpdate() override;

            void Move(Entity entity, float speed);

        private:
            InputSystem& m_input_system;
    };
}