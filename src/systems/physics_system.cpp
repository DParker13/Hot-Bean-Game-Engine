#include "physics_system.hpp"

namespace Systems {
    PhysicsSystem::PhysicsSystem(Core::CoreManager& coreManager)
        : System(coreManager) {
        coreManager.RegisterSystem<PhysicsSystem>(this);
        
        coreManager.SetSignature<PhysicsSystem, Components::Transform>();
        coreManager.SetSignature<PhysicsSystem, Components::RigidBody>();
    }

    void PhysicsSystem::OnUpdate(float deltaTime) {
        for (auto& entity : _entities) {
            auto& transform = _coreManager.GetComponent<Components::Transform>(entity);
            auto& rigidbody = _coreManager.GetComponent<Components::RigidBody>(entity);

            transform.position.y -= rigidbody.velocity.y * deltaTime;
		    rigidbody.velocity.y += rigidbody.gravity * deltaTime;
        }
    }

    std::string PhysicsSystem::ToString() const {
        return "  Physics System Entities: " + std::to_string(_entities.size()) + "\n";
    }
}