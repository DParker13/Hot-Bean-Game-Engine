#include "physics_system.hpp"

namespace Systems {
    void PhysicsSystem::Update(Core::CoreManager& coreManager, float dt) {
        for (auto& entity : _entities) {
            auto& transform = coreManager.GetComponent<Components::Transform>(entity);
            auto const& gravity = coreManager.GetComponent<Components::Gravity>(entity);
            auto& rigidbody = coreManager.GetComponent<Components::RigidBody>(entity);

            transform.position += rigidbody.velocity * dt;

		    rigidbody.velocity += gravity.force * dt;
        }
    }

    void PhysicsSystem::Print() const {
        std::cout << "  Physics System Entities: " << _entities.size() << std::endl;
    }
}