/**
 * @file player_controller_system.cpp
 * @author Daniel Parker
 * @brief System for applying player input to entities.
 * @version 0.1
 * @date 2024-12-20
 * 
 * @copyright Copyright (c) 2024
 */

#include <HotBeanEngine/defaults/systems/input/player_controller_system.hpp>

namespace HBE::Default::Systems {
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
        auto keys_pressed = m_input_system.m_keys_pressed;
        
        if (keys_pressed.size() > 0) {
            float distance = speed * g_app.GetDeltaTime();

            auto& controller = g_ecs.GetComponent<Controller>(entity);

            if (controller.controllable) {
                auto& transform = g_ecs.GetComponent<Transform2D>(entity);

                if (keys_pressed.find(SDLK_LEFT) != keys_pressed.end()) {
                    transform.m_local_position.x -= distance;
                }
                
                if (keys_pressed.find(SDLK_RIGHT) != keys_pressed.end()) {
                    transform.m_local_position.x += distance;
                }
                
                if (keys_pressed.find(SDLK_UP) != keys_pressed.end()) {
                    transform.m_local_position.y -= distance;
                }
                
                if (keys_pressed.find(SDLK_DOWN) != keys_pressed.end()) {
                    transform.m_local_position.y += distance;
                }
            }
        }
    }
}