#include "render_system.hpp"

namespace Systems {
    RenderSystem::RenderSystem(Core::CoreManager& coreManager) {
        coreManager.RegisterSystem<Systems::RenderSystem>();

        coreManager.SetSignature<Systems::RenderSystem, Components::Transform>();
        coreManager.SetSignature<Systems::RenderSystem, Components::Texture>();
    }
    
    void RenderSystem::Render(SDL_Surface* surface, SDL_Renderer* renderer, Core::CoreManager& coreManager) {
        SDL_Color color = { 0xFF, 0xFF, 0xFF, 0xFF };

        for (auto& entity : _entities) {
            auto& transform = coreManager.GetComponent<Components::Transform>(entity);
            auto& texture = coreManager.GetComponent<Components::Texture>(entity);

            //CreateRect(surface, renderer, &color, &transform);
            const SDL_Rect* rect = new SDL_Rect({ (int)transform.position.x, (int)transform.position.y, 200, 50 });
            SDL_RenderCopy(renderer, texture.texture, NULL, rect);
        }
    }

    // Function to fill a rectangle on an SDL_Surface
    void RenderSystem::CreateRect(SDL_Surface* surface, SDL_Renderer* renderer,
                                SDL_Color* color, Components::Transform* transform) {
        int width = surface->w;
        int height = surface->h;

        SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);

        // Define a rectangle
        SDL_FRect fillRect = { transform->position.x, transform->position.y, 10, 10 };

        // Fill the rectangle with the current drawing color
        SDL_RenderFillRectF(renderer, &fillRect);
    }

    std::string RenderSystem::ToString() const {
        return "  Render System Entities: " + std::to_string(_entities.size()) + "\n";
    }
}