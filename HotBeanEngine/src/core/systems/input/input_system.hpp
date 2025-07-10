#pragma once

#include <unordered_set>

#include "../../application/all_application.hpp"

using namespace Core::Application;
using namespace Core::ECS;

namespace Core::Systems {
    class InputSystem : public System {
        public:
            std::unordered_set<SDL_Keycode> m_keys_pressed;
            
            InputSystem() = default;

            void SetSignature() override;
            void OnEvent(SDL_Event& event) override;
    };
}