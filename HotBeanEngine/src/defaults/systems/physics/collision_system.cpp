/**
 * @file collision_system.cpp
 * @author Daniel Parker
 * @brief System for managing 2D collision shapes in the physics world.
 * @version 0.1
 * @date 2025-03-25
 *
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/defaults/systems/physics/collision_system.hpp>

namespace HBE::Default::Systems {
    void CollisionSystem::OnUpdate() {}

    void CollisionSystem::OnEntityAdded(EntityID entity) {
        auto collider = g_ecs.GetComponent<Collider2D>(entity);
        auto rigidbody = g_ecs.GetComponent<RigidBody>(entity);

        b2ShapeDef shape_def = b2DefaultShapeDef();
        shape_def.density = 1.0f;
        shape_def.material.friction = 0.3f;

        switch (collider.m_shape) {
        case Collider2D::ColliderShape::Box: {
            b2Polygon box = b2MakeBox(collider.m_size.x / 2.0f, collider.m_size.y / 2.0f);
            b2CreatePolygonShape(rigidbody.m_body_id, &shape_def, &box);
            break;
        }
        case Collider2D::ColliderShape::Circle: {
            b2Circle circle = b2Circle{{0.0f, 0.0f}, collider.m_size.x / 2.0f};
            b2CreateCircleShape(rigidbody.m_body_id, &shape_def, &circle);
            break;
        }
        }
    }
} // namespace HBE::Default::Systems