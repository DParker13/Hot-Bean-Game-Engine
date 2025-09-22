#pragma once

#include <SDL.h>

namespace HBE::Core {
    struct GameLoop {
        virtual void OnStart() = 0;
        virtual void OnPreEvent() = 0;
        virtual void OnEvent(SDL_Event& event) = 0;
        virtual void OnWindowResize(SDL_Event& event) = 0;
        virtual void OnUpdate() = 0;
        virtual void OnRender() = 0;
        virtual void OnPostRender() = 0;
    };
    
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
}