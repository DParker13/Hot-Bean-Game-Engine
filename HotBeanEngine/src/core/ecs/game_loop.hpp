#pragma once

#include <SDL.h>

namespace Core {
    namespace ECS {
        struct GameLoop {
            virtual void OnInit() = 0;
            virtual void OnPreEvent() = 0;
            virtual void OnEvent(SDL_Event& event) = 0;
            virtual void OnUpdate() = 0;
            virtual void OnRender() = 0;
            virtual void OnPostRender() = 0;
        };
        
        enum class GameLoopState {
            OnInit,
            OnPreEvent,
            OnEvent,
            OnUpdate,
            OnRender,
            OnPostRender
        };
    }
}