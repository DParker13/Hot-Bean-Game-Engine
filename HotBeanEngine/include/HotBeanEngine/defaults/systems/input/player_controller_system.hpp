#pragma once

#include <HotBeanEngine/defaults/systems/input/input_system.hpp>
#include <HotBeanEngine/defaults/components/default_components.hpp>

using namespace HBE::Default::Components;
using namespace HBE::Application;
using namespace HBE::Core;

namespace HBE::Default::Systems {
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