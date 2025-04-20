#include "ui_system.hpp"

namespace Systems {
    UISystem::UISystem(std::string font_path) : System(), _font_path(font_path), _font(nullptr) {
        App::GetInstance().SetupSystem<UISystem, Transform2D, Text, Texture>(this);
    }

    UISystem::~UISystem() {
        TTF_CloseFont(_font); // This causes a segmentation fault on exit for some reason
        _font = nullptr;
    }

    void UISystem::OnInit() {
        SetupFont();
    }

    void UISystem::OnEvent(SDL_Event& event) {
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
            for (auto& entity : _entities) {
                auto& text = App::GetInstance().GetECSManager()->GetComponent<Text>(entity);

                text._dirty = true;
            }
        }
    }

    /**
     * Updates all UI element textures
     */
    void UISystem::OnUpdate() {
        for (auto& entity : _entities) {
            auto& ui_element = App::GetInstance().GetECSManager()->GetComponent<UIElement>(entity);

            switch(ui_element._type) {
                case Enums::UIType::Text:
                    OnUpdateText(entity);
            }

            OnUpdateTexture(entity);
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

    void UISystem::OnUpdateTexture(Entity entity) {
        App& app = App::GetInstance();
        auto* renderer = app.GetRenderer();

        auto& transform = app.GetECSManager()->GetComponent<Transform2D>(entity);
        auto& texture = app.GetECSManager()->GetComponent<Texture>(entity);

        if (texture._texture) {
            const SDL_Rect* rect = new SDL_Rect({ (int)transform._position.x, (int)transform._position.y, texture._size.x, texture._size.y });
            
            if (SDL_RenderCopy(renderer, texture._texture, NULL, rect) < 0) {
                std::cerr << "Error: " << SDL_GetError() << std::endl;
                return;
            }

            if (rect) {
                delete rect;
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

    std::string UISystem::ToString() const {
        return "  UI System Entities: " + std::to_string(_entities.size()) + "\n";
    }
}