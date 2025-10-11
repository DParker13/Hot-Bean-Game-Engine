#pragma once

#include <unordered_set>

#include <HotBeanEngine/application/application.hpp>

using namespace HBE::Application;
using namespace HBE::Core;

namespace HBE::Default::Systems {
    class InputSystem : public System {
        public:
            // TODO: Make configurable
            //static const SDL_Keycode DEBUG_KEY = SDLK_F1;

            std::unordered_set<SDL_Keycode> m_keys_pressed;
            std::unordered_set<Uint8> m_mouse_buttons_pressed;
            glm::vec2 m_mouse_position = {0.0f, 0.0f};
            
            DEFINE_SIGNATURE(InputSystem);
            InputSystem() = default;

            void OnEvent(SDL_Event& event) override;

        private:
            void OnKeyDown(SDL_Event& event);
            void OnKeyUp(SDL_Event& event);
            void OnMouseButtonDown(SDL_Event& event);
            void OnMouseButtonUp(SDL_Event& event);
            void OnMouseMove(SDL_Event& event);
    };
}