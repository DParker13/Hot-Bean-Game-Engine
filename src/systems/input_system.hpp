#pragma once

#include <SDL.h>
#include <memory>
#include <iostream>
#include <unordered_map>

#include "../core/ecs.hpp"
#include "../core/core_manager.hpp"
#include "../components/transform.hpp"

namespace Systems {
    class InputSystem : public System {
        public:
            float speed = 1000.0f;
            
            void HandleEvent(Core::CoreManager& coreManager, SDL_Event& event, float dt);
            void Print() const;
        
        private:
            std::unordered_map<SDL_Keycode, bool> _keysPressed;

            bool UpdateInput(SDL_Event& event);
    };
}