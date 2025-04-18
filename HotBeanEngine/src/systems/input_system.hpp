#pragma once

#include <SDL.h>
#include <unordered_set>
#include <core.hpp>

using namespace Core::Application;
using namespace Core::ECS;

namespace Systems {
    class InputSystem : public System {
        public:
            std::unordered_set<SDL_Keycode> _keysPressed;
            
            InputSystem(App& app);
            void OnEvent(SDL_Event& event) override;
            std::string ToString() const;
            
    };
}