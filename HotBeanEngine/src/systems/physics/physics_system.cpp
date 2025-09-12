#include "physics_system.hpp"

namespace Systems {
    PhysicsSystem::PhysicsSystem(InputSystem& input_system) : m_input_system(input_system) {}
    
    /**
     * @brief Updates the physics of all entities in the system.
     * @details Applies gravity to all entities in the system.
     */
    void PhysicsSystem::OnUpdate() {
        for (auto& entity : m_entities) {
            auto& transform = g_ecs.GetComponent<Transform2D>(entity);
            auto& rigidbody = g_ecs.GetComponent<RigidBody>(entity);

            transform.m_world_position.y -= rigidbody.velocity.y * g_app.GetDeltaTime();
		    rigidbody.velocity.y += rigidbody.gravity * g_app.GetDeltaTime();
        }
    }
}