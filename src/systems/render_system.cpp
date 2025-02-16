#include "render_system.hpp"

namespace Systems {
    RenderSystem::RenderSystem(Core::CoreManager& coreManager)
        : System(coreManager) {
        coreManager.RegisterSystem<RenderSystem>(this);

        coreManager.SetSignature<RenderSystem, Components::Transform>();
        coreManager.SetSignature<RenderSystem, Components::Texture>();
    }
    
    /**
     * Renders all entities with a Transform and Texture component to the screen.
     *
     * This function is part of the System interface and is called by the Application layer.
     * It is responsible for rendering all entities that have both a Transform and Texture component.
     *
     * @param surface The SDL_Surface to render to.
     * @param renderer The SDL_Renderer to render with.
     * @param coreManager The CoreManager to get the entities from.
     */
    void RenderSystem::Render(SDL_Surface* surface, SDL_Renderer* renderer, Core::CoreManager& coreManager) {
        SDL_Color color = { 0xFF, 0xFF, 0xFF, 0xFF };

        for (auto& entity : _entities) {
            auto& transform = coreManager.GetComponent<Components::Transform>(entity);
            auto& texture = coreManager.GetComponent<Components::Texture>(entity);

            //CreateRect(surface, renderer, &color, &transform);
            const SDL_Rect* rect = new SDL_Rect({ (int)transform.position.x, (int)transform.position.y, 200, 50 });
            SDL_RenderCopy(renderer, texture._texture, NULL, rect);
        }
    }

    std::string RenderSystem::ToString() const {
        return "  Render System Entities: " + std::to_string(_entities.size()) + "\n";
    }
}