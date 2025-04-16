#include "collision_system.hpp"

namespace Systems {
    CollisionSystem::CollisionSystem(App& app, int resolution)
        : System(app) {
        app.SetupSystem<CollisionSystem, Transform2D, RigidBody, Collider2D>(this);

        _grid = std::vector<int>(resolution * resolution, 0);
    }

    /**
     * @brief Updates the physics of all entities in the system.
     * @details Applies gravity to all entities in the system.
     */
    void CollisionSystem::OnUpdate() {
        //TODO: Add a grid to check collisions locally instead of iterating through all entities

        for (auto& entity : _entities) {
            for (auto& other_entity : _entities) {
                bool collision = CheckCollision(entity, other_entity);

                if (collision) {
                    ResolveCollision(entity, other_entity);
                }
            }
        }
    }

    bool CollisionSystem::CheckCollision(Entity entity_one, Entity entity_two) {
        auto& transform_one = _app.GetECSManager()->GetComponent<Transform2D>(entity_one);
        auto& transform_two = _app.GetECSManager()->GetComponent<Transform2D>(entity_two);

        auto& collider_one = _app.GetECSManager()->GetComponent<Collider2D>(entity_one);
        auto& collider_two = _app.GetECSManager()->GetComponent<Collider2D>(entity_two);

        // Bounding box one (top, right, bottom, left)
        float bounding_box_one[] = {transform_one._position.y,
                                    transform_one._position.x + collider_one._bounding_box.x,
                                    transform_one._position.y + collider_one._bounding_box.y,
                                    transform_one._position.x };
        // Bounding box two (top, right, bottom, left)
        float bounding_box_two[] = {transform_two._position.y,
                                    transform_two._position.x + collider_two._bounding_box.x,
                                    transform_two._position.y + collider_two._bounding_box.y,
                                    transform_two._position.x };


        // AABB collision
        // Check if the bounding boxes of the two entities overlap
        if ((bounding_box_one[0] >= bounding_box_two[2] || /* top of one is below bottom of two */
            bounding_box_one[2] <= bounding_box_two[0]) && /* bottom of one is above top of two */
            (bounding_box_one[1] >= bounding_box_two[3] || /* right of one is left of two */
            bounding_box_one[3] <= bounding_box_two[1]))   /* left of one is right of two */
        {
            return true;
        }
        else {
            return false;
        }
    }

    void CollisionSystem::ResolveCollision(Entity entity_one, Entity entity_two) {
        auto& collider_one = _app.GetECSManager()->GetComponent<Collider2D>(entity_one);
        auto& collider_two = _app.GetECSManager()->GetComponent<Collider2D>(entity_two);
        
        // Check if either entity is a trigger (no need to update physics/transforms)
        if (collider_one._is_trigger || collider_two._is_trigger) {
            return;
        }
        else {
            auto& transform_one = _app.GetECSManager()->GetComponent<Transform2D>(entity_one);
            auto& transform_two = _app.GetECSManager()->GetComponent<Transform2D>(entity_two);
            //auto& rigidbody_one = _app.GetComponent<RigidBody>(entity_one);
            //auto& rigidbody_two = _app.GetComponent<RigidBody>(entity_two);

            // Calculate the collision normal
            float dx = transform_one._position.x - transform_two._position.x;
            float dy = transform_one._position.y - transform_two._position.y;
            float collision_normal_x = dx / (dx * dx + dy * dy);
            float collision_normal_y = dy / (dx * dx + dy * dy);

            // Move each entity out of the collision
            transform_one._position.x += collision_normal_x * collider_one._bounding_box.x;
            transform_one._position.y += collision_normal_y * collider_one._bounding_box.y;
            transform_two._position.x -= collision_normal_x * collider_two._bounding_box.x;
            transform_two._position.y -= collision_normal_y * collider_two._bounding_box.y;
        }
    }

    std::string CollisionSystem::ToString() const {
        return "  Physics System Entities: " + std::to_string(_entities.size()) + "\n";
    }
}