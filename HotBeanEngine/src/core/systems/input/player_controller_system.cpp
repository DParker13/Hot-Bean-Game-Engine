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
        for (auto& entity : m_entities) {
            Move(entity, 100);
        }
    }

    /**
     * Moves the given entity based on the given input keys and time elapsed since the last frame.
     *
     * @param entity The entity to move.
     * @param speed The speed at which the entity will move, in pixels per second.
     */
    void PlayerControllerSystem::Move(Entity entity, float speed) {
        App& app = App::GetInstance();
        auto keys_pressed = m_input_system.m_keys_pressed;
        
        if (keys_pressed.size() > 0) {
            float distance = speed * app.GetDeltaTime();

            auto& controller = app.GetECSManager()->GetComponent<Controller>(entity);

            if (controller.controllable) {
                auto& transform = app.GetECSManager()->GetComponent<Transform2D>(entity);

                if (keys_pressed.find(SDLK_LEFT) != keys_pressed.end()) {
                    transform.m_world_position.x -= distance;
                }
                
                if (keys_pressed.find(SDLK_RIGHT) != keys_pressed.end()) {
                    transform.m_world_position.x += distance;
                }
                
                if (keys_pressed.find(SDLK_UP) != keys_pressed.end()) {
                    transform.m_world_position.y -= distance;
                }
                
                if (keys_pressed.find(SDLK_DOWN) != keys_pressed.end()) {
                    transform.m_world_position.y += distance;
                }
            }
        }
    }
}