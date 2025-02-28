#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <unordered_set>

#include "../core/managers/core_manager.hpp"
#include "../components/transform-2d.hpp"
#include "../components/text.hpp"
#include "../components/texture.hpp"

namespace Systems {
    class UISystem : public System {
        public:
            std::unordered_set<SDL_Keycode> _keysPressed;
            TTF_Font* _font = nullptr;
            Uint32 _framesCounter = 0;
            Uint32 _lastTickCount = 0;
            Uint32 _fps = 0;
            
            UISystem(Core::CoreManager& coreManager);
            ~UISystem();
            UISystem(const UISystem& other) = delete;
            UISystem& operator=(const UISystem& other) = delete;

            //System interface
            void OnUpdate(SDL_Renderer* renderer, float deltaTime) override;

            std::string ToString() const;
        private:
            const std::filesystem::path _font_path = std::filesystem::current_path().parent_path() / "assets" / "fonts" / "LT_Superior_Mono" / "LTSuperiorMono-Regular.ttf";
            //std::unordered_map<Uint32, SDL_Font*> _font_pool;
            
    };
}