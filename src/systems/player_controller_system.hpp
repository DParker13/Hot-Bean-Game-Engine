#pragma once

#include <SDL.h>
#include <unordered_set>
#include <core.hpp>

#include "input_system.hpp"
#include "../components/transform_2d.hpp"
#include "../components/controller.hpp"

using namespace Components;
using namespace Core::Application;
using namespace Core::ECS;

namespace Systems {
    class PlayerControllerSystem : public System {
        public:
            PlayerControllerSystem(App& app);

            void OnUpdate() override;

            void Move(Entity entity, std::unordered_set<SDL_Keycode> keysPressed, float speed);
            std::string ToString() const;
    };
}