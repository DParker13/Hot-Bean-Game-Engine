#include "ui_system.hpp"

namespace Systems {
    UISystem::UISystem(Core::CoreManager& coreManager)
        : System(coreManager) {
        coreManager.RegisterSystem<UISystem>(this);

        coreManager.SetSignature<UISystem, Components::Transform>();
        coreManager.SetSignature<UISystem, Components::Text>();

        auto fontPath = std::filesystem::current_path().parent_path() / "assets" / "fonts" / "LT_Superior_Mono" / "LTSuperiorMono-Regular.ttf";
        _font = TTF_OpenFont(fontPath.string().data(), 10);

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

    void UISystem::OnUpdate(float deltaTime) {
        for (auto& entity : _entities) {
            auto& transform = _coreManager.GetComponent<Components::Transform>(entity);
            auto& text = _coreManager.GetComponent<Components::Text>(entity);

            if (!text._font) {
                text._font = _font;
            }

            _framesCounter++;
            if (_lastTickCount < SDL_GetTicks() - 1000) {
                _lastTickCount = SDL_GetTicks();
                _fps = _framesCounter;
                _framesCounter = 0;

                text._prevText = text._text;
                text._text = "FPS: " + std::to_string(_fps);
            }
        }
    }

    void UISystem::OnRender(SDL_Renderer* renderer, SDL_Window* window, SDL_Surface* surface) {
        for (auto& entity : _entities) {
            auto& transform = _coreManager.GetComponent<Components::Transform>(entity);
            auto& text = _coreManager.GetComponent<Components::Text>(entity);

            if (text._font && text._text != "") {
                const SDL_Rect* rect = new SDL_Rect({ (int)transform.position.x, (int)transform.position.y, 200, 50 });

                if (text._prevText != text._text) {
                    _texture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Solid(text._font, text._text.data(), text._color));

                    if (SDL_RenderCopy(renderer, _texture, NULL, rect) < 0) {
                        std::cerr << "Error: " << SDL_GetError() << std::endl;
                        return;
                    }
                    
                    SDL_DestroyTexture(_texture);
                }
            }
        }
    }

    std::string UISystem::ToString() const {
        return "  UI System Entities: " + std::to_string(_entities.size()) + "\n";
    }
}