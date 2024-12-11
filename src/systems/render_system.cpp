#include "render_system.hpp"

namespace Systems {
    void RenderSystem::Render(SDL_Surface* surface, SDL_Renderer* renderer, Core::CoreManager& coreManager) {
        SDL_Color color = { 0xFF, 0xFF, 0xFF, 0xFF };

        for (auto& entity : _entities) {
            auto& transform = coreManager.GetComponent<Components::Transform>(entity);
            CreateRect(surface, renderer, &color, &transform);
        }
    }

    // Function to fill a rectangle on an SDL_Surface
    void RenderSystem::CreateRect(SDL_Surface* surface, SDL_Renderer* renderer, SDL_Color* color, Components::Transform* transform) {
        int width = surface->w;
        int height = surface->h;

        SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);

        // Define a rectangle
        SDL_FRect fillRect = { transform->position.x, transform->position.y, 10, 10 };

        // Fill the rectangle with the current drawing color
        SDL_RenderFillRectF(renderer, &fillRect);
    }

    void RenderSystem::Print() const {
        std::cout << "  Render System Entities: " << _entities.size() << std::endl;
    }
}