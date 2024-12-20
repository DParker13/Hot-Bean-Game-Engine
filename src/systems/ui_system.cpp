#include "ui_system.hpp"

namespace Systems {
    UISystem::UISystem(Core::CoreManager& coreManager) {
        coreManager.RegisterSystem<Systems::UISystem>();

        coreManager.SetSignature<Systems::UISystem, Components::Transform>();
        coreManager.SetSignature<Systems::UISystem, Components::Text>();
    }

    void UISystem::Update(Core::CoreManager& coreManager) {
        for (auto& entity : _entities) {
            auto& transform = coreManager.GetComponent<Components::Transform>(entity);
            auto& text = coreManager.GetComponent<Components::Text>(entity);

            if (text.font == nullptr) {
                text.Init();
            }

            _framesCounter++;
            if (_lastTickCount < SDL_GetTicks() - 1000) {
                _lastTickCount = SDL_GetTicks();
                _fps = _framesCounter;
                _framesCounter = 0;

                text.text = "FPS: " + std::to_string(_fps);
            }
        }
    }

    void UISystem::Render(SDL_Surface* surface, SDL_Renderer* renderer, Core::CoreManager& coreManager) {
        for (auto& entity : _entities) {
            auto& transform = coreManager.GetComponent<Components::Transform>(entity);
            auto& text = coreManager.GetComponent<Components::Text>(entity);

            if (text.font != nullptr && text.text != "") {
                const SDL_Rect* rect = new SDL_Rect({ (int)transform.position.x, (int)transform.position.y, 200, 50 });
                _texture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Solid(text.font, text.text.data(), text.color));
                if (SDL_RenderCopy(renderer, _texture, NULL, rect) < 0) {
                    std::cout << "Error: " << SDL_GetError() << std::endl;
                    std::cout << text.text << std::endl;
                    std::cout << text.text.data() << std::endl;
                }
                SDL_DestroyTexture(_texture);
            }
        }
    }

    std::string UISystem::ToString() const {
        return "  UI System Entities: " + std::to_string(_entities.size()) + "\n";
    }
}