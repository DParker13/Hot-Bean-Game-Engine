#include "physics_system.hpp"

namespace Systems {
    PhysicsSystem::PhysicsSystem() : System() {
        App::GetInstance().SetupSystem<PhysicsSystem, Transform2D, RigidBody>(this);
    }

    /**
     * @brief Updates the physics of all entities in the system.
     * @details Applies gravity to all entities in the system.
     */
    void PhysicsSystem::OnUpdate() {
        App& app = App::GetInstance();

        for (auto& entity : _entities) {
            auto& transform = app.GetECSManager()->GetComponent<Transform2D>(entity);
            auto& rigidbody = app.GetECSManager()->GetComponent<RigidBody>(entity);

            transform._position.y -= rigidbody.velocity.y * app.GetDeltaTime();
		    rigidbody.velocity.y += rigidbody.gravity * app.GetDeltaTime();
        }
    }

    std::string PhysicsSystem::ToString() const {
        return "  Physics System Entities: " + std::to_string(_entities.size()) + "\n";
    }
}