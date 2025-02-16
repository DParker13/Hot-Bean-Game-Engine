#include "ui_system.hpp"

namespace Systems {
    UISystem::UISystem(Core::CoreManager& coreManager)
        : System(coreManager) {
        coreManager.RegisterSystem<UISystem>(this);

        coreManager.SetSignature<UISystem, Components::Transform>();
        coreManager.SetSignature<UISystem, Components::Text>();
        coreManager.SetSignature<UISystem, Components::Texture>();

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

    /**
     * Updates all UI entities.
     *
     * This function is part of the System interface and is called by the Application layer.
     * It is responsible for updating all UI entities that have both a Transform, Text, and Texture component.
     *
     * @param deltaTime The time elapsed since the last update in seconds.
     */
    void UISystem::OnUpdate(float deltaTime) {
        for (auto& entity : _entities) {
            auto& transform = _coreManager.GetComponent<Components::Transform>(entity);
            auto& text = _coreManager.GetComponent<Components::Text>(entity);
            auto& texture = _coreManager.GetComponent<Components::Texture>(entity);

            // Initialize font
            if (!text._font) {
                text._font = _font;
            }

            _framesCounter++;
            // if (_lastTickCount < SDL_GetTicks() - 1000) {
            //     _lastTickCount = SDL_GetTicks();
            //     _fps = _framesCounter;
            //     _framesCounter = 0;

            //     text.SetText("FPS: " + std::to_string(_fps));
            // }

            if (text._text_updated) {
                text._surface = TTF_RenderUTF8_Solid_Wrapped(_font, text.GetChar(), text._color, texture._size.x);
                // Update texture size
                if (TTF_SizeUTF8(_font, text.GetChar(), &texture._size.x, &texture._size.y) == -1) {
                    std::cerr << "Text sizing error: " << TTF_GetError() << std::endl;
                }
            }
        }
    }

    /**
     * Renders all UI entities to the screen.
     *
     * This function is part of the System interface and is called by the
     * Application layer. It is responsible for rendering all UI entities
     * that have both a Transform, Text, and Texture component.
     *
     * @param renderer The SDL_Renderer to render to.
     * @param window The SDL_Window that the renderer is attached to.
     * @param surface The SDL_Surface to render to.
     *
     * @throws None
     */
    void UISystem::OnRender(SDL_Renderer* renderer, SDL_Window* window, SDL_Surface* surface) {
        for (auto& entity : _entities) {
            auto& transform = _coreManager.GetComponent<Components::Transform>(entity);
            auto& text = _coreManager.GetComponent<Components::Text>(entity);
            auto& texture = _coreManager.GetComponent<Components::Texture>(entity);

            // Update texture with new surface
            if (text._font && text.GetString() != "" && text._text_updated) {
                texture._texture = SDL_CreateTextureFromSurface(renderer, text._surface);
                text._text_updated = false;
            }

            if (texture._texture) {
                const SDL_Rect* rect = new SDL_Rect({ (int)transform.position.x, (int)transform.position.y, texture._size.x, texture._size.y });
                
                if (SDL_RenderCopy(renderer, texture._texture, NULL, rect) < 0) {
                    std::cerr << "Error: " << SDL_GetError() << std::endl;
                    return;
                }

                delete rect;
            }
        }
    }

    std::string UISystem::ToString() const {
        return "  UI System Entities: " + std::to_string(_entities.size()) + "\n";
    }
}