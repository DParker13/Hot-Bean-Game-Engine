#include "physics_system.hpp"

namespace Systems {
    PhysicsSystem::PhysicsSystem(App& app)
        : System(app) {
        app.GetCoreManager().RegisterSystem<PhysicsSystem>(this);
        
        app.GetCoreManager().SetSignature<PhysicsSystem, Transform2D, RigidBody>();
    }

    /**
     * @brief Updates the physics of all entities in the system.
     * @details Applies gravity to all entities in the system.
     */
    void PhysicsSystem::OnUpdate() {
        auto& coreManager = _app.GetCoreManager();

        for (auto& entity : _entities) {
            auto& transform = coreManager.GetComponent<Transform2D>(entity);
            auto& rigidbody = coreManager.GetComponent<RigidBody>(entity);

            transform._position.y -= rigidbody.velocity.y * _app.GetDeltaTime();
		    rigidbody.velocity.y += rigidbody.gravity * _app.GetDeltaTime();
        }
    }

    std::string PhysicsSystem::ToString() const {
        return "  Physics System Entities: " + std::to_string(_entities.size()) + "\n";
    }
}