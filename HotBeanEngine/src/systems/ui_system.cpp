#include "ui_system.hpp"

namespace Systems {
    UISystem::UISystem(std::string font_path) : System(), _font_path(font_path), _font(nullptr) {}

    UISystem::~UISystem() {
        TTF_CloseFont(_font); // This causes a segmentation fault on exit for some reason
        _font = nullptr;
    }

    void UISystem::SetSignature() {
        SETUP_SYSTEM(UISystem, Transform2D, Text, Texture);
    }

    void UISystem::OnStart() {
        SetupFont();
    }

    void UISystem::OnWindowResize(SDL_Event& event) {
        for (auto& entity : m_entities) {
            auto& text = App::GetInstance().GetECSManager()->GetComponent<Text>(entity);

            text._dirty = true;
        }
    }

    /**
     * Updates all UI element textures
     */
    void UISystem::OnUpdate() {
        for (auto& entity : m_entities) {
            auto& text = App::GetInstance().GetECSManager()->GetComponent<Text>(entity);

            switch(text._type) {
                case UIElement::UIType::Text:
                    OnUpdateText(entity);
            }
        }
    }

    void UISystem::OnUpdateText(Entity entity) {
        App& app = App::GetInstance();
        auto* renderer = app.GetRenderer();

        auto& text = app.GetECSManager()->GetComponent<Text>(entity);
        auto& texture = app.GetECSManager()->GetComponent<Texture>(entity);

        // Initialize font
        if (!text._font) {
            text._font = _font;
        }
        
        // Update text texture if dirty
        if (text._dirty) {
            // Render text to surface
            SDL_Surface* surface = TTF_RenderUTF8_Solid_Wrapped(_font, text.GetChar(), text._color, text._wrapping_width);

            // Update texture with new surface
            if (text._font && text.GetString() != "") {
                texture._texture = SDL_CreateTextureFromSurface(renderer, surface);
                texture._size = { surface->w, surface->h };
                SDL_SetTextureBlendMode(texture._texture, SDL_BLENDMODE_BLEND);
                text._dirty = false;
            }
        }
    }

    void UISystem::SetupFont() {
        _font = TTF_OpenFont(_font_path.data(), 10);

        if (!_font) {
            SDL_Log("Couldn't load font: %s\n", SDL_GetError());
        }
        else {
            TTF_SetFontStyle(_font, TTF_STYLE_NORMAL);
            TTF_SetFontOutline(_font, 0);
            TTF_SetFontKerning(_font, 1);
            TTF_SetFontHinting(_font, TTF_HINTING_MONO);
        }
    }
}