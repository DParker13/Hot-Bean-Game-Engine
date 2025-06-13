#pragma once

#include "input_system.hpp"

using namespace Core::Components;
using namespace Core::Application;
using namespace Core::ECS;

namespace Core::Systems {
    class PlayerControllerSystem : public System {
        public:
            PlayerControllerSystem() = default;

            void SetSignature() override;
            void OnUpdate() override;

            void Move(Entity entity, std::unordered_set<SDL_Keycode> keysPressed, float speed);
    };
}