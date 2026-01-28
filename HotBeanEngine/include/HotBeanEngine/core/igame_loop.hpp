/**
 * @file igame_loop.hpp
 * @author Daniel Parker (DParker13)
 * @brief Interface for the game loop structure.
 * @version 0.1
 * @date 2025-03-02
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <SDL3/SDL.h>

namespace HBE::Core {
    /// @brief Interface for the game loop structure.
    struct IGameLoop {
        virtual void OnStart() = 0;
        virtual void OnPreEvent() = 0;
        virtual void OnEvent(SDL_Event &event) = 0;
        virtual void OnWindowResize(SDL_Event &event) = 0;
        virtual void OnUpdate() = 0;
        virtual void OnRender() = 0;
        virtual void OnPostRender() = 0;
    };

    /// @brief Enumeration of game loop states.
    enum class GameLoopState {
        OnStart,
        OnPreEvent,
        OnEvent,
        OnWindowResize,
        OnFixedUpdate,
        OnUpdate,
        OnRender,
        OnPostRender
    };
} // namespace HBE::Core