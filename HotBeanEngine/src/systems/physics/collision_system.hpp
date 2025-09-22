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
#include "glm/trigonometric.hpp"
#include "glm/common.hpp"
#include "glm/glm.hpp"
#include "glm/matrix.hpp"

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

            void OnStart() override;
            void OnUpdate() override;

        private:
            struct MTV {
                glm::vec2 axis;
                float overlap;
            };
            
            void ResolveCollision(Entity entity_one, Entity entity_two);
            bool CheckCollision(Entity entity_one, Entity entity_two);
            bool CheckBoxBoxCollision(const Transform2D& t1, const Collider2D& c1,
                                      const Transform2D& t2, const Collider2D& c2);

            std::vector<glm::vec2> GetBoxCorners(const Transform2D& t, const glm::vec2& size);

            bool OverlapOnAxis(const std::vector<glm::vec2>& a,
                               const std::vector<glm::vec2>& b,
                               const glm::vec2& axis);

            void ProjectOntoAxis(const std::vector<glm::vec2>& corners,
                                 const glm::vec2& axis,
                                 float& min, float& max);

            glm::vec2 RotateVec2(const glm::vec2& v, float radians);
            bool CheckBoxBoxCollisionMTV(const Transform2D& t1, const glm::vec2& size1,
                                         const Transform2D& t2, const glm::vec2& size2,
                                         MTV& outMTV);

            void UpdateOctree();
    };
}