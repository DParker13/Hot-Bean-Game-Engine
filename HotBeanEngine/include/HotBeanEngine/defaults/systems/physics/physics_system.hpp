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

#include <HotBeanEngine/defaults/systems/input/input_system.hpp>
#include <HotBeanEngine/defaults/components/default_components.hpp>

namespace HBE::Default::Systems {
    using HBE::Core::System;
    using HBE::Default::Systems::InputSystem;
    using HBE::Default::Components::Transform2D;
    using HBE::Default::Components::RigidBody;
    /**
     * @brief Integrates Box2D physics simulation
     * 
     * Manages physics world and rigid body updates.
     * Synchronizes physics state with entity transforms.
     */
    class PhysicsSystem : public System {
    private:
        InputSystem& m_input_system;
        glm::vec2 m_gravity = {0.0f, 9.8f};
        b2WorldId m_world_id = b2WorldId();

    public:
        DEFINE_SIGNATURE(PhysicsSystem, "Physics System", Transform2D, RigidBody);
            
        PhysicsSystem(InputSystem& input_system, glm::vec2 gravity)
            : System(), m_input_system(input_system), m_gravity(gravity) {}

        PhysicsSystem(InputSystem& input_system)
            : PhysicsSystem(input_system, glm::vec2(0.0f, 9.8f)) {}

        void OnStart() override;
        void OnFixedUpdate() override;
        void OnEntityAdded(Entity entity) override;
        void OnEntityRemoved(Entity entity) override;

    private:
        float DegreesToRadians(float degrees);
        float RadiansToDegrees(float radians);
    };
}