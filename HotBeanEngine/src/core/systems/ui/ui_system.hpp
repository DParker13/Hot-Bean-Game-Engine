#pragma once

#include <unordered_set>

#include "../../application/all_application.hpp"

using namespace Core::Components;
using namespace Core::Application;
using namespace Core::ECS;

namespace Core::Systems {
    class UISystem : public System {
        public:
            std::unordered_set<SDL_Keycode> _keysPressed;
            TTF_Font* m_font = nullptr;
            
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
            void OnUpdateTextBox(Entity entity);
            void OnUpdateImage(Entity entity);
            void OnUpdateButton(Entity entity);
            void OnUpdateSlider(Entity entity);
            void OnUpdateDropdown(Entity entity);
            void OnUpdateCheckbox(Entity entity);
            void OnUpdateRadio(Entity entity);
            
    };
}