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

#include <box2d/box2d.h>
#include <glm/glm.hpp>

#include <HotBeanEngine/core/isystem.hpp>
#include <HotBeanEngine/defaults/components/miscellaneous/transform_2d.hpp>
#include <HotBeanEngine/defaults/components/physics/rigidbody.hpp>

namespace HBE::Default::Systems {
    using HBE::Core::EntityID;
    using HBE::Default::Components::RigidBody;
    using HBE::Default::Components::Transform2D;

    /**
     * @brief Integrates Box2D physics simulation
     *
     * Manages physics world and rigid body updates.
     * Synchronizes physics state with entity transforms.
     */
    class PhysicsSystem : public HBE::Core::ISystem {
    public:
        REQUIRES_COMPONENTS(Transform2D, RigidBody);
        DEFINE_NAME("Physics System")

    private:
        glm::vec2 m_gravity = {0.0f, 9.8f};
        b2WorldId m_world_id = b2WorldId();

    public:
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
} // namespace HBE::Default::Systems