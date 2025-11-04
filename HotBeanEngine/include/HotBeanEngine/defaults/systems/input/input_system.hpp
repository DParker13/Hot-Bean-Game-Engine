/**
 * @file input_system.hpp
 * @author Daniel Parker (DParker13)
 * @brief System for handling user input.
 * @version 0.1
 * @date 2025-03-02
 * 
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <unordered_set>

#include <HotBeanEngine/application/application.hpp>

namespace HBE::Default::Systems {
    using namespace HBE::Core;
    
    /**
     * @brief System for handling user input.
     */
    class InputSystem : public ISystem {
    public:
        // TODO: Make configurable
        //static const SDL_Keycode DEBUG_KEY = SDLK_F1;

        std::unordered_set<SDL_Keycode> m_keys_pressed;
        std::unordered_set<Uint8> m_mouse_buttons_pressed;
        glm::vec2 m_mouse_position = {0.0f, 0.0f};
        
        DEFINE_SIGNATURE(InputSystem, "Input System");
        InputSystem() = default;
        ~InputSystem() = default;

        void OnEvent(SDL_Event& event) override;

    private:
        void OnKeyDown(SDL_Event& event);
        void OnKeyUp(SDL_Event& event);
        void OnMouseButtonDown(SDL_Event& event);
        void OnMouseButtonUp(SDL_Event& event);
        void OnMouseMove(SDL_Event& event);
    };
}