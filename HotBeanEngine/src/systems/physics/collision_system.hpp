/**
 * @file collision_system.hpp
 * @author Daniel Parker (DParker13)
 * @brief System for 2D collision detection. Currently uses AABB collision detection.
 * Will be updated to use other collision detection algorithms in the future.
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
        private:
            Octree2D<int>* m_octree;

        public:
            DEFINE_SIGNATURE(CollisionSystem, Transform2D, RigidBody, Collider2D);
            CollisionSystem(int depth);
            ~CollisionSystem();

            void OnUpdate() override;

        private:
            bool CheckCollision(Entity entity_one, Entity entity_two);
            void ResolveCollision(Entity entity_one, Entity entity_two);
            void UpdateOctree();
    };
}