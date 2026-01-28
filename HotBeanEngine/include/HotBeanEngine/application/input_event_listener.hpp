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

#include <HotBeanEngine/core/all_core.hpp>

namespace HBE::Application {
    /**
     * @brief System for handling user input.
     */
    class InputEventListener {
    private:
        std::unordered_set<SDL_Keycode> m_keys_pressed;
        std::unordered_set<Uint8> m_mouse_buttons_pressed;
        glm::vec2 m_mouse_position = {0.0f, 0.0f};

    public:
        InputEventListener() = default;
        ~InputEventListener() = default;

        void OnEvent(SDL_Event &event);
        const std::unordered_set<SDL_Keycode> &GetKeysPressed() const { return m_keys_pressed; }
        const std::unordered_set<Uint8> &GetMouseButtonsPressed() const { return m_mouse_buttons_pressed; }
        const glm::vec2 &GetMousePosition() const { return m_mouse_position; }

    protected:
        virtual void OnKeyDown(SDL_Event &event) {};
        virtual void OnKeyUp(SDL_Event &event) {};
        virtual void OnMouseButtonDown(SDL_Event &event) {};
        virtual void OnMouseButtonUp(SDL_Event &event) {};
        virtual void OnMouseMove(SDL_Event &event) {};
    };
} // namespace HBE::Application