#pragma once

#include <iostream>
#include <unordered_set>
#include <core.hpp>

#include "../components/transform_2d.hpp"
#include "../components/text.hpp"
#include "../components/texture.hpp"

using namespace Components;
using namespace Core::Application;
using namespace Core::ECS;

namespace Systems {
    class UISystem : public System {
        public:
            std::unordered_set<SDL_Keycode> _keysPressed;
            TTF_Font* _font = nullptr;
            
            UISystem(App& app);
            ~UISystem();

            //System interface
            void OnEvent(SDL_Event& event) override;
            void OnUpdate() override;

            std::string ToString() const;
        private:
            const std::filesystem::path _font_path = std::filesystem::current_path().parent_path() / "assets" / "fonts" / "LT_Superior_Mono" / "LTSuperiorMono-Regular.ttf";

            void SetupFont();
            void OnUpdateText(Entity entity);
            void OnUpdateTexture(Entity entity);
            
    };
}