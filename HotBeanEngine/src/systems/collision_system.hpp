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

#include "../core/core.hpp"

using namespace Components;
using namespace Core::Application;

namespace Systems {
    class CollisionSystem : public System {
        public:
            CollisionSystem(int resolution);

            void SetSignature() override;
            void OnUpdate() override;

        private:
            std::vector<int> _grid;

            bool CheckCollision(Entity entity_one, Entity entity_two);
            void ResolveCollision(Entity entity_one, Entity entity_two);
    };
}