#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <unordered_set>

#include "../core/managers/core_manager.hpp"
#include "../components/transform.hpp"
#include "../components/text.hpp"
#include "../components/texture.hpp"

namespace Systems {
    class UISystem : public System {
        public:
            std::unordered_set<SDL_Keycode> _keysPressed;
            TTF_Font* _font;
            Uint32 _framesCounter = 0;
            Uint32 _lastTickCount = 0;
            Uint32 _fps = 0;
            
            UISystem(Core::CoreManager& coreManager);

            //System interface
            void OnUpdate(float deltaTime) override;
            void OnRender(SDL_Renderer* renderer, SDL_Window* window, SDL_Surface* surface) override;

            std::string ToString() const;
            
    };
}