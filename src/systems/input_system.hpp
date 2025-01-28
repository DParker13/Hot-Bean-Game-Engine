#pragma once

#include <SDL.h>
#include <unordered_set>

#include "../core/managers/core_manager.hpp"

namespace Systems {
    class InputSystem : public System {
        public:
            std::unordered_set<SDL_Keycode> _keysPressed;
            
            InputSystem(Core::CoreManager& coreManager);
            void OnEvent(SDL_Event& event) override;
            std::string ToString() const;
            
    };
}