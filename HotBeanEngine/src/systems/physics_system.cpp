#include "physics_system.hpp"

namespace Systems {
    void PhysicsSystem::SetSignature() {
        SETUP_SYSTEM(PhysicsSystem, Transform2D, RigidBody);
    }

    /**
     * @brief Updates the physics of all entities in the system.
     * @details Applies gravity to all entities in the system.
     */
    void PhysicsSystem::OnUpdate() {
        App& app = App::GetInstance();

        for (auto& entity : m_entities) {
            auto& transform = app.GetECSManager()->GetComponent<Transform2D>(entity);
            auto& rigidbody = app.GetECSManager()->GetComponent<RigidBody>(entity);

            transform.m_world_position.y -= rigidbody.velocity.y * app.GetDeltaTime();
		    rigidbody.velocity.y += rigidbody.gravity * app.GetDeltaTime();
        }
    }
}