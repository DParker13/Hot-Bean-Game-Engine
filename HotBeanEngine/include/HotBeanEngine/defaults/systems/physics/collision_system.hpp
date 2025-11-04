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
    using namespace HBE::Core;
    using namespace HBE::Default::Components;

    /**
     * @brief System for 2D collision detection.
     */
    class CollisionSystem : public ISystem {
    public:
        DEFINE_SIGNATURE(CollisionSystem, "Collision System", Transform2D, RigidBody, Collider2D);
        CollisionSystem() = default;
        ~CollisionSystem() = default;

        void OnUpdate() override;
        void OnEntityAdded(EntityID entity) override;
    };
}