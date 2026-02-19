/**
 * @file collision_system.hpp
 * @author Daniel Parker (DParker13)
 * @brief System for 2D collision detection.
 * @version 0.1
 * @date 2025-03-02
 *
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <HotBeanEngine/core/isystem.hpp>
#include <HotBeanEngine/defaults/components/miscellaneous/transform_2d.hpp>
#include <HotBeanEngine/defaults/components/physics/collider_2d.hpp>
#include <HotBeanEngine/defaults/components/physics/rigidbody.hpp>

namespace HBE::Default::Systems {
    using HBE::Core::EntityID;
    using HBE::Default::Components::Transform2D;
    using HBE::Default::Components::Collider2D;
    using HBE::Default::Components::RigidBody;

    /**
     * @brief System for 2D collision detection.
     */
    class CollisionSystem : public HBE::Core::ISystem {
    public:
        REQUIRES_COMPONENTS(Transform2D, RigidBody, Collider2D);
        DEFINE_NAME("Collision System")

        CollisionSystem() = default;
        ~CollisionSystem() = default;

        void OnUpdate() override;
        void OnEntityAdded(EntityID entity) override;
    };
} // namespace HBE::Default::Systems