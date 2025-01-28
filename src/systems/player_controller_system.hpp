#pragma once

#include <SDL.h>
#include <unordered_set>

#include "input_system.hpp"
#include "../core/managers/core_manager.hpp"
#include "../components/transform.hpp"
#include "../components/player.hpp"

namespace Systems {
    class PlayerControllerSystem : public System {
        public:
            PlayerControllerSystem(Core::CoreManager& coreManager);

            void OnUpdate(float deltaTime) override;

            void Move(Entity entity, std::unordered_set<SDL_Keycode> keysPressed, float deltaTime, float speed);
            std::string ToString() const;
    };
}