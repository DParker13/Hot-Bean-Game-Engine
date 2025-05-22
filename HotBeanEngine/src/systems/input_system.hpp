#pragma once

#include <unordered_set>

#include "../core/core.hpp"

using namespace Core::Application;
using namespace Core::ECS;

namespace Systems {
    class InputSystem : public System {
        public:
            std::unordered_set<SDL_Keycode> _keysPressed;
            
            InputSystem() = default;

            void SetSignature() override;
            void OnEvent(SDL_Event& event) override;
    };
}