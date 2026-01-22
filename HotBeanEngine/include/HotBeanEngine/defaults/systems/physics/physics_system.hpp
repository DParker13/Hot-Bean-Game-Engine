/**
 * @file physics_system.hpp
 * @author Daniel Parker (DParker13)
 * @brief System for simulating 2D physics in the game world using Box2D.
 * @version 0.1
 * @date 2025-03-02
 * 
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/defaults/components/default_components.hpp>

namespace HBE::Default::Systems {
    using namespace HBE::Core;
    using namespace HBE::Default::Components;
    
    /**
     * @brief Integrates Box2D physics simulation
     * 
     * Manages physics world and rigid body updates.
     * Synchronizes physics state with entity transforms.
     */
    class PhysicsSystem : public ISystem {
    private:
        glm::vec2 m_gravity = {0.0f, 9.8f};
        b2WorldId m_world_id = b2WorldId();

    public:
        DEFINE_SIGNATURE(PhysicsSystem, "Physics System", Transform2D, RigidBody);
            
        PhysicsSystem(glm::vec2 gravity) : m_gravity(gravity) {}

        PhysicsSystem() : PhysicsSystem(glm::vec2(0.0f, 9.8f)) {}
        void OnStart() override;
        void OnFixedUpdate() override;
        void OnEntityAdded(EntityID entity) override;
        void OnEntityRemoved(EntityID entity) override;

    private:
        float DegreesToRadians(float degrees);
        float RadiansToDegrees(float radians);
    };
}