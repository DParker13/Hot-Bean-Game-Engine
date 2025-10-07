#include "physics_system.hpp"

namespace Systems {
    void PhysicsSystem::OnStart() {
        b2WorldDef world = b2DefaultWorldDef();
        world.gravity = b2Vec2({m_gravity.x, m_gravity.y});
        m_world_id = b2CreateWorld(&world);
    }

    /**
     * @brief Updates the physics of all entities in the system.
     * @details Applies forces, integrates motion, and clears forces.
     */
    void PhysicsSystem::OnFixedUpdate() {
        float time_step = 1.0f / 60.0f;
        int sub_step_count = 4;

        // Step the physics world forward
        b2World_Step(m_world_id, time_step, sub_step_count);

        for (auto& entity : m_entities) {
            auto& transform = g_ecs.GetComponent<Transform2D>(entity);
            auto& rigidbody = g_ecs.GetComponent<RigidBody>(entity);

            b2Vec2 position = b2Body_GetPosition(rigidbody.m_body_id);
            b2Rot rotation = b2Body_GetRotation(rigidbody.m_body_id);
            transform.m_local_position = {position.x, position.y};
            transform.m_local_rotation = RadiansToDegrees(atan2(rotation.s, rotation.c));
        }
    }

    void PhysicsSystem::OnEntityAdded(Entity entity) {
        auto& transform = g_ecs.GetComponent<Transform2D>(entity);
        auto& rigidbody = g_ecs.GetComponent<RigidBody>(entity);

        b2BodyDef body_def = b2DefaultBodyDef();
        body_def.position = b2Vec2({transform.m_local_position.x, transform.m_local_position.y});
        body_def.rotation = b2MakeRot(DegreesToRadians(transform.m_local_rotation));
        body_def.type = rigidbody.m_type;

        b2BodyId body_id = b2CreateBody(m_world_id, &body_def);
        rigidbody.m_body_id = body_id;
    }

    /**
     * @brief Destroys and removes the rigidbody from the physics simulation.
     * @param entity The entity to remove.
     */
    void PhysicsSystem::OnEntityRemoved(Entity entity) {
        auto& rigidbody = g_ecs.GetComponent<RigidBody>(entity);
        b2DestroyBody(rigidbody.m_body_id);
    }
}