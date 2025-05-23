#pragma once

#include <unordered_set>

#include "../core/core.hpp"

using namespace Components;
using namespace Core::Application;
using namespace Core::ECS;

namespace Systems {
    class UISystem : public System {
        public:
            std::unordered_set<SDL_Keycode> _keysPressed;
            TTF_Font* _font = nullptr;
            
            UISystem(std::string font_path);
            ~UISystem();

            //System interface
            void SetSignature() override;
            void OnStart() override;
            void OnWindowResize(SDL_Event& event) override;
            void OnUpdate() override;
        private:
            const std::string _font_path;

            void SetupFont();
            void OnUpdateText(Entity entity);
            
    };
}