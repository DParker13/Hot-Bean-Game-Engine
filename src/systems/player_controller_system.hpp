#pragma once

#include <SDL.h>
#include <unordered_set>

#include "../managers/core_manager.hpp"
#include "../components/transform.hpp"
#include "../components/player.hpp"

namespace Systems {
    class PlayerControllerSystem : public System {
        public:
            PlayerControllerSystem(Core::CoreManager& coreManager);
            void Move(Core::CoreManager& coreManager, std::unordered_set<SDL_Keycode> keysPressed, float dt, float speed);
            std::string ToString() const;
    };
}