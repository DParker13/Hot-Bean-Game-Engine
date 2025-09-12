#pragma once

#include <unordered_set>

#include "../../application/all_application.hpp"

using namespace HBE::Components;
using namespace HBE::Application;
using namespace HBE::Core;

namespace Systems {
    class UISystem : public System {
        private:
            const std::string _font_path;

        public:
            std::unordered_set<SDL_Keycode> _keysPressed;
            TTF_Font* m_font = nullptr; // This is not a good idea
            
            DEFINE_SIGNATURE(UISystem, Transform2D, Texture, UIElement);
            UISystem(std::string font_path);
            ~UISystem();

            //System interface
            void OnStart() override;
            void OnWindowResize(SDL_Event& event) override;
            void OnUpdate() override;
        
        private:
            void SetupFont();
            void OnUpdateText(Entity entity);
            void OnUpdateTextBox(Entity entity);
            void OnUpdateImage(Entity entity);
            void OnUpdateButton(Entity entity);
            void OnUpdateSlider(Entity entity);
            void OnUpdateDropdown(Entity entity);
            void OnUpdateCheckbox(Entity entity);
            void OnUpdateRadio(Entity entity);
            
    };
}