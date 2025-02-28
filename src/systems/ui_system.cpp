#include "ui_system.hpp"

namespace Systems {
    UISystem::UISystem(Core::CoreManager& coreManager)
        : System(coreManager), _font(nullptr) {
        coreManager.RegisterSystem<UISystem>(this);

        coreManager.SetSignature<UISystem, Components::Transform2D>();
        coreManager.SetSignature<UISystem, Components::Text>();
        coreManager.SetSignature<UISystem, Components::Texture>();

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
        TTF_CloseFont(_font);
        _font = nullptr;
    }

    /**
     * Updates all UI element textures
     *
     *
     * @param renderer The SDL_Renderer to render to.
     * @param deltaTime The time elapsed since the last update in seconds.
     *
     * @throws None
     */
    void UISystem::OnUpdate(SDL_Renderer* renderer, float deltaTime) {
        for (auto& entity : _entities) {
            auto& transform = _coreManager.GetComponent<Components::Transform2D>(entity);
            auto& text = _coreManager.GetComponent<Components::Text>(entity);
            auto& texture = _coreManager.GetComponent<Components::Texture>(entity);

            _framesCounter++;

            // Initialize font
            if (!text._font) {
                text._font = _font;
            }
            
            if (text._awaiting_update) {
                text._surface = TTF_RenderUTF8_Solid_Wrapped(_font, text.GetChar(), text._color, texture._size.x);
                // Update texture size
                // if (TTF_SizeUTF8(_font, text.GetChar(), &texture._size.x, &texture._size.y) == -1) {
                //     std::cerr << "Text sizing error: " << TTF_GetError() << std::endl;
                //     return;
                // }
            }

            // Update texture with new surface
            if (text._font && text.GetString() != "" && text._awaiting_update) {
                texture._texture = SDL_CreateTextureFromSurface(renderer, text._surface);
                SDL_SetTextureBlendMode(texture._texture, SDL_BLENDMODE_BLEND);
                text._awaiting_update = false;
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