#pragma once

#include <SDL.h>
#include <unordered_set>

#include "input_system.hpp"

#include "../core/managers/core_manager.hpp"

#include "../components/transform-2d.hpp"
#include "../components/controller.hpp"

namespace Systems {
    class PlayerControllerSystem : public System {
        public:
            PlayerControllerSystem(Core::CoreManager& coreManager);

            void OnUpdate(SDL_Renderer* renderer, float deltaTime) override;

            void Move(Entity entity, std::unordered_set<SDL_Keycode> keysPressed, float deltaTime, float speed);
            std::string ToString() const;
    };
}