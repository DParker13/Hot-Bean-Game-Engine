#include "ui_system.hpp"

namespace Systems {
    UISystem::UISystem(App& app)
        : System(app), _font(nullptr) {
        app.GetCoreManager().RegisterSystem<UISystem>(this);

        app.GetCoreManager().SetSignature<UISystem, Transform2D, Text, Texture>();

        _font = TTF_OpenFont(_font_path.string().data(), 10);

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

    UISystem::~UISystem() {
        TTF_CloseFont(_font); // This causes a segmentation fault on exit for some reason
        _font = nullptr;
    }

    void UISystem::OnEvent(SDL_Event& event) {
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
            for (auto& entity : _entities) {
                auto& text = _app.GetCoreManager().GetComponent<Text>(entity);

                text._awaiting_update = true;
            }
        }
    }

    /**
     * Updates all UI element textures
     */
    void UISystem::OnUpdate() {
        auto& coreManager = _app.GetCoreManager();
        auto* renderer = _app.GetRenderer();

        for (auto& entity : _entities) {
            auto& transform = coreManager.GetComponent<Transform2D>(entity);
            auto& text = coreManager.GetComponent<Text>(entity);
            auto& texture = coreManager.GetComponent<Texture>(entity);

            // Initialize font
            if (!text._font) {
                text._font = _font;
            }
            
            if (text._awaiting_update) {
                // Render text to surface
                text._surface = TTF_RenderUTF8_Solid_Wrapped(_font, text.GetChar(), text._color, text._wrapping_width);

                // Update texture with new surface
                if (text._font && text.GetString() != "") {
                    texture._texture = SDL_CreateTextureFromSurface(renderer, text._surface);
                    texture._size = { text._surface->w, text._surface->h };
                    SDL_SetTextureBlendMode(texture._texture, SDL_BLENDMODE_BLEND);
                    text._awaiting_update = false;
                }
            }

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
    }

    std::string UISystem::ToString() const {
        return "  UI System Entities: " + std::to_string(_entities.size()) + "\n";
    }
}