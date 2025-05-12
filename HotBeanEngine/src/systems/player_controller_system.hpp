#pragma once

#include <unordered_set>

#include "input_system.hpp"

using namespace Components;
using namespace Core::Application;
using namespace Core::ECS;

namespace Systems {
    class PlayerControllerSystem : public System {
        public:
            PlayerControllerSystem();

            void OnUpdate() override;

            void Move(Entity entity, std::unordered_set<SDL_Keycode> keysPressed, float speed);
    };
}