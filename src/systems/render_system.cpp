#include "render_system.hpp"

namespace Systems {
    RenderSystem::RenderSystem(Core::CoreManager& coreManager)
        : System(coreManager) {
        coreManager.RegisterSystem<RenderSystem>(this);

        coreManager.SetSignature<RenderSystem, Components::Transform>();
        coreManager.SetSignature<RenderSystem, Components::Texture>();
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

    std::string RenderSystem::ToString() const {
        return "  Render System Entities: " + std::to_string(_entities.size()) + "\n";
    }
}