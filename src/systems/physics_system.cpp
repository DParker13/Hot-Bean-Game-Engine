#include "physics_system.hpp"

namespace Systems {
    PhysicsSystem::PhysicsSystem(Core::CoreManager& coreManager) {
        coreManager.RegisterSystem<PhysicsSystem>(this);
        
        coreManager.SetSignature<PhysicsSystem, Components::Transform>();
        coreManager.SetSignature<PhysicsSystem, Components::RigidBody>();
    }

    void PhysicsSystem::Update(Core::CoreManager& coreManager, float dt) {
        for (auto& entity : _entities) {
            auto& transform = coreManager.GetComponent<Components::Transform>(entity);
            auto& rigidbody = coreManager.GetComponent<Components::RigidBody>(entity);

            transform.position.y -= rigidbody.velocity.y * dt;
		    rigidbody.velocity.y += rigidbody.gravity * dt;
        }
    }

    std::string PhysicsSystem::ToString() const {
        return "  Physics System Entities: " + std::to_string(_entities.size()) + "\n";
    }
}