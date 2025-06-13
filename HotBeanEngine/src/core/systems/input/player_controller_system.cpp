#include "player_controller_system.hpp"

namespace Core::Systems {
    void PlayerControllerSystem::SetSignature() {
        SETUP_SYSTEM(PlayerControllerSystem, Transform2D, Controller);
    }

    /**
     * Updates the state of all entities managed by the PlayerControllerSystem.
     * This function is called every frame and processes input to move entities.
     */
    void PlayerControllerSystem::OnUpdate() {
        auto keysPressed = App::GetInstance().GetECSManager()->GetSystem<Systems::InputSystem>()->_keysPressed;

        for (auto& entity : m_entities) {
            Move(entity, keysPressed, 100);
        }
    }

    /**
     * Moves the given entity based on the given input keys and time elapsed since the last frame.
     *
     * @param entity The entity to move.
     * @param keysPressed The set of keys currently pressed.
     * @param speed The speed at which the entity will move, in pixels per second.
     */
    void PlayerControllerSystem::Move(Entity entity, std::unordered_set<SDL_Keycode> keysPressed, float speed) {
        App& app = App::GetInstance();
        
        if (keysPressed.size() > 0) {
            float distance = speed * app.GetDeltaTime();

            auto& controller = app.GetECSManager()->GetComponent<Controller>(entity);

            if (controller.controllable) {
                auto& transform = app.GetECSManager()->GetComponent<Transform2D>(entity);

                if (keysPressed.find(SDLK_LEFT) != keysPressed.end()) {
                    transform.m_world_position.x -= distance;
                }
                
                if (keysPressed.find(SDLK_RIGHT) != keysPressed.end()) {
                    transform.m_world_position.x += distance;
                }
                
                if (keysPressed.find(SDLK_UP) != keysPressed.end()) {
                    transform.m_world_position.y -= distance;
                }
                
                if (keysPressed.find(SDLK_DOWN) != keysPressed.end()) {
                    transform.m_world_position.y += distance;
                }
            }
        }
    }
}