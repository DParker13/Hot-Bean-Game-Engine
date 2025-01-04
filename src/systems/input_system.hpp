#pragma once

#include <SDL.h>
#include <unordered_set>

#include "../managers/core_manager.hpp"

namespace Systems {
    class InputSystem : public System {
        public:
            std::unordered_set<SDL_Keycode> _keysPressed;
            
            InputSystem(Core::CoreManager& coreManager);
            void UpdateKeys(SDL_Event& event);
            std::string ToString() const;
            
    };
}