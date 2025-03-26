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

#include <core.hpp>

#include "../components/transform_2d.hpp"
#include "../components/rigidbody.hpp"
#include "../components/collider_2d.hpp"

using namespace Components;
using namespace Core::Application;

namespace Systems {
    class CollisionSystem : public System {
        private:
            std::vector<int> _grid;

            bool CheckCollision(Entity entity_one, Entity entity_two);
            void ResolveCollision(Entity entity_one, Entity entity_two);

        public:
            CollisionSystem(App& app, int resolution);

            //System interface
            void OnUpdate() override;

            std::string ToString() const;
    };
}