#include "collision_system.hpp"

namespace Systems {
    CollisionSystem::CollisionSystem(int depth) : System() {
        m_octree = new Octree2D<int>(glm::ivec3(0, 0, Config::SCREEN_HEIGHT), depth);
    }

    CollisionSystem::~CollisionSystem() {
        delete m_octree;
    }

    void CollisionSystem::OnStart() {
        // Insert all entities into the octree
        // std::vector<glm::ivec3> all_bounds = m_octree->GetAllBounds();
        // for (int i = 0; i < all_bounds.size(); i++) {
        //     Entity e = g_ecs.CreateEntity();

        //     Transform2D transform = Transform2D();
        //     transform.m_local_position = glm::vec2(all_bounds[i].x, all_bounds[i].y);
        //     transform.m_layer = 0;

        //     Shape shape = Shape();
        //     shape.m_type = Shape::ShapeType::Box;
        //     shape.m_size = glm::vec2(all_bounds[i].z, all_bounds[i].z);
        //     shape.m_color = { 255, 0, 0, 255 };

        //     g_ecs.AddComponent<Shape>(e, shape);
        //     g_ecs.AddComponent<Transform2D>(e, transform);
        //     g_ecs.AddComponent<Texture>(e);
        // }
    }

    /**
     * @brief Main update loop for the collision system.
     * Checks for collisions between entities and resolves them.
     */
    void CollisionSystem::OnUpdate() {
        // TODO: Update octree with new positions (ignore transforms from camera system, maybe use world position, not camera position)
        // Should this be done using the transform system?
        UpdateOctree();

        // TODO: Check for collisions within octree nodes
        // TODO: Add ability for item to be in multiple octree nodes if it is on/near the edge of another node
        for (auto& entity : m_entities) {
            for (auto& other_entity : m_entities) {
                bool collision = CheckCollision(entity, other_entity);

                if (collision) {
                    ResolveCollision(entity, other_entity);
                }
            }
        }
    }

    void CollisionSystem::ResolveCollision(Entity entity_one, Entity entity_two) {
        auto& rbA = g_ecs.GetComponent<RigidBody>(entity_one);
        auto& rbB = g_ecs.GetComponent<RigidBody>(entity_two);
        auto& cA = g_ecs.GetComponent<Collider2D>(entity_one);
        auto& cB = g_ecs.GetComponent<Collider2D>(entity_two);
        auto& tA = g_ecs.GetComponent<Transform2D>(entity_one);
        auto& tB = g_ecs.GetComponent<Transform2D>(entity_two);

        if (cA.m_is_trigger || cB.m_is_trigger) 
            return;

        MTV mtv;
        if (CheckBoxBoxCollisionMTV(tA, cA.m_size, tB, cB.m_size, mtv)) {
            float invMassA = rbA.GetInvMass();
            float invMassB = rbB.GetInvMass();

            // If both are static -> no resolution needed
            if (invMassA == 0.0f && invMassB == 0.0f)
                return;

            // --- Positional correction ---
            glm::vec2 correction = mtv.axis * mtv.overlap;
            float totalInvMass = invMassA + invMassB;

            if (invMassA > 0.0f) {
                float ratioA = invMassA / totalInvMass;
                tA.m_local_position -= correction * ratioA;
            }
            if (invMassB > 0.0f) {
                float ratioB = invMassB / totalInvMass;
                tB.m_local_position += correction * ratioB;
            }

            // --- Velocity resolution (impulse) ---
            glm::vec2 normal = glm::normalize(mtv.axis);
            float vA = glm::dot(rbA.GetVelocity(), normal);
            float vB = glm::dot(rbB.GetVelocity(), normal);

            // Relative velocity must be separating to apply impulse
            if (vA - vB > 0.0f) 
                return;

            float e = 0.5f; // restitution (bounciness)
            float j = -(1.0f + e) * (vA - vB);
            if (totalInvMass > 0.0f)
                j /= totalInvMass;

            // Apply impulses
            if (invMassA > 0.0f)
                rbA.SetVelocity(rbA.GetVelocity() + (j * invMassA) * normal);
            if (invMassB > 0.0f)
                rbB.SetVelocity(rbB.GetVelocity() - (j * invMassB) * normal);
        }
    }

    bool CollisionSystem::CheckBoxBoxCollisionMTV(const Transform2D& t1, const glm::vec2& size1,
                                const Transform2D& t2, const glm::vec2& size2,
                                MTV& outMTV)
    {
        auto cornersA = GetBoxCorners(t1, size1);
        auto cornersB = GetBoxCorners(t2, size2);

        std::vector<glm::vec2> axes = {
            glm::normalize(cornersA[1] - cornersA[0]),
            glm::normalize(cornersA[3] - cornersA[0]),
            glm::normalize(cornersB[1] - cornersB[0]),
            glm::normalize(cornersB[3] - cornersB[0])
        };

        float minOverlap = std::numeric_limits<float>::max();
        glm::vec2 smallestAxis;

        for (auto& axis : axes) {
            glm::vec2 perp(-axis.y, axis.x);
            float minA, maxA, minB, maxB;
            ProjectOntoAxis(cornersA, perp, minA, maxA);
            ProjectOntoAxis(cornersB, perp, minB, maxB);

            float overlap = std::min(maxA, maxB) - std::max(minA, minB);
            if (overlap <= 0) return false; // separating axis found

            if (overlap < minOverlap) {
                minOverlap = overlap;
                smallestAxis = perp;
            }
        }

        outMTV.axis = glm::normalize(smallestAxis);
        outMTV.overlap = minOverlap;
        return true;
    }

    bool CollisionSystem::CheckCollision(Entity entity_one, Entity entity_two) {
        auto& t1 = g_ecs.GetComponent<Transform2D>(entity_one);
        auto& t2 = g_ecs.GetComponent<Transform2D>(entity_two);
        auto& c1 = g_ecs.GetComponent<Collider2D>(entity_one);
        auto& c2 = g_ecs.GetComponent<Collider2D>(entity_two);

        // Skip static-static
        if (c1.m_is_static && c2.m_is_static)
            return false;

        if (c1.m_shape == Collider2D::ColliderShape::Square &&
            c2.m_shape == Collider2D::ColliderShape::Square) {
            return CheckBoxBoxCollision(t1, c1, t2, c2);
        }

        // TODO: Circle vs Circle and Box vs Circle
        return false;
    }

    bool CollisionSystem::CheckBoxBoxCollision(const Transform2D& t1, const Collider2D& c1,
                              const Transform2D& t2, const Collider2D& c2) {
        auto cornersA = GetBoxCorners(t1, c1.m_size);
        auto cornersB = GetBoxCorners(t2, c2.m_size);

        // Axes to test (edges of both boxes)
        std::vector<glm::vec2> axes = {
            glm::normalize(cornersA[1] - cornersA[0]),
            glm::normalize(cornersA[3] - cornersA[0]),
            glm::normalize(cornersB[1] - cornersB[0]),
            glm::normalize(cornersB[3] - cornersB[0])
        };

        for (auto axis : axes) {
            glm::vec2 perp(-axis.y, axis.x);  // perpendicular axis
            if (!OverlapOnAxis(cornersA, cornersB, perp))
                return false; // separating axis found
        }

        return true; // no separating axis -> collision
    }


    std::vector<glm::vec2> CollisionSystem::GetBoxCorners(const Transform2D& t, const glm::vec2& size) {
        std::vector<glm::vec2> corners = {
            {0, 0},
            {size.x, 0},
            {size.x, size.y},
            {0, size.y}
        };

        for (auto& corner : corners) {
            corner = RotateVec2(corner, t.m_local_rotation) + t.m_local_position;
        }

        return corners;
    }

    void CollisionSystem::ProjectOntoAxis(const std::vector<glm::vec2>& corners,
                     const glm::vec2& axis,
                     float& min, float& max) {
        min = max = glm::dot(corners[0], axis);
        for (size_t i = 1; i < corners.size(); i++) {
            float proj = glm::dot(corners[i], axis);
            if (proj < min) min = proj;
            if (proj > max) max = proj;
        }
    }

    bool CollisionSystem::OverlapOnAxis(const std::vector<glm::vec2>& a,
                    const std::vector<glm::vec2>& b,
                    const glm::vec2& axis) {
        float minA, maxA, minB, maxB;
        ProjectOntoAxis(a, axis, minA, maxA);
        ProjectOntoAxis(b, axis, minB, maxB);
        return !(maxA < minB || maxB < minA);
    }

    glm::vec2 CollisionSystem::RotateVec2(const glm::vec2& v, float degrees) {
        float radians = glm::radians(degrees);
        float c = cos(radians);
        float s = sin(radians);
        return {
            v.x * c - v.y * s,
            v.x * s + v.y * c
        };
    }

    void CollisionSystem::UpdateOctree() {
        
    }
}