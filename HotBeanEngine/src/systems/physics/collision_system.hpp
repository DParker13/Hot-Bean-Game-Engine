/**
 * @file collision_system.hpp
 * @author Daniel Parker (DParker13)
 * @brief System for 2D collision detection.
 * @version 0.1
 * @date 2025-03-02
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once

#include "../../application/all_application.hpp"

using namespace HBE::Components;
using namespace HBE::Application;
using namespace HBE::Core;

namespace Systems {
    class CollisionSystem : public System {
        public:
            DEFINE_SIGNATURE(CollisionSystem, Transform2D, RigidBody, Collider2D);
            CollisionSystem() : System() {}
            ~CollisionSystem() = default;

            void OnUpdate() override;
            void OnEntityAdded(Entity entity) override;
    };
}