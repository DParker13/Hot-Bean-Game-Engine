#include "physics_system.hpp"

namespace Systems {
    PhysicsSystem::PhysicsSystem(App& app)
        : System(app) {
        app.SetupSystem<PhysicsSystem, Transform2D, RigidBody>(this);
    }

    /**
     * @brief Updates the physics of all entities in the system.
     * @details Applies gravity to all entities in the system.
     */
    void PhysicsSystem::OnUpdate() {
        for (auto& entity : _entities) {
            auto& transform = _app.GetECSManager()->GetComponent<Transform2D>(entity);
            auto& rigidbody = _app.GetECSManager()->GetComponent<RigidBody>(entity);

            transform._position.y -= rigidbody.velocity.y * _app.GetDeltaTime();
		    rigidbody.velocity.y += rigidbody.gravity * _app.GetDeltaTime();
        }
    }

    std::string PhysicsSystem::ToString() const {
        return "  Physics System Entities: " + std::to_string(_entities.size()) + "\n";
    }
}