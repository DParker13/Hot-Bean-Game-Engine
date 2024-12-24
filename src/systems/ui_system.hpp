#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <unordered_set>

#include "../managers/core_manager.hpp"
#include "../components/transform.hpp"
#include "../components/texture.hpp"
#include "../components/text.hpp"

namespace Systems {
    class UISystem : public System {
        public:
            std::unordered_set<SDL_Keycode> _keysPressed;
            SDL_Texture* _texture;
            Uint32 _framesCounter = 0;
            Uint32 _lastTickCount = 0;
            Uint32 _fps = 0;
            
            UISystem() = default;
            UISystem(Core::CoreManager& coreManager);
            void Render(SDL_Surface* surface, SDL_Renderer* renderer, Core::CoreManager& coreManager);
            void Update(Core::CoreManager& coreManager);
            std::string ToString() const;
            
    };
}