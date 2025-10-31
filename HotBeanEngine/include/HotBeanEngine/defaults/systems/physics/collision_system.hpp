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

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/defaults/components/default_components.hpp>

namespace HBE::Default::Systems {
    using HBE::Core::System;
    using HBE::Default::Components::Transform2D;
    using HBE::Default::Components::RigidBody;
    using HBE::Default::Components::Collider2D;

    /**
     * @brief System for 2D collision detection.
     */
    class CollisionSystem : public System {
        public:
            DEFINE_SIGNATURE(CollisionSystem, "Collision System", Transform2D, RigidBody, Collider2D);
            CollisionSystem() = default;
            ~CollisionSystem() = default;

            void OnUpdate() override;
            void OnEntityAdded(Entity entity) override;
    };
}