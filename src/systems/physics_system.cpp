#include "physics_system.hpp"

namespace Systems {
    PhysicsSystem::PhysicsSystem(Core::CoreManager& coreManager)
        : System(coreManager) {
        coreManager.RegisterSystem<PhysicsSystem>(this);
        
        coreManager.SetSignature<PhysicsSystem, Components::Transform2D>();
        coreManager.SetSignature<PhysicsSystem, Components::RigidBody>();
    }

    /**
     * @brief Updates the physics of all entities in the system.
     * @details Applies gravity to all entities in the system.
     * @param deltaTime The time elapsed since the last frame in seconds.
     */
    void PhysicsSystem::OnUpdate(SDL_Renderer* renderer, float deltaTime) {
        for (auto& entity : _entities) {
            auto& transform = _coreManager.GetComponent<Components::Transform2D>(entity);
            auto& rigidbody = _coreManager.GetComponent<Components::RigidBody>(entity);

            transform._position.y -= rigidbody.velocity.y * deltaTime;
		    rigidbody.velocity.y += rigidbody.gravity * deltaTime;
        }
    }

    std::string PhysicsSystem::ToString() const {
        return "  Physics System Entities: " + std::to_string(_entities.size()) + "\n";
    }
}