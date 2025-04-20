/**
 * @file entity_manager.h
 * @author Daniel Parker (DParker13)
 * @brief Manages the creation and destruction of entities.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once

#include <SDL_stdinc.h>
#include <array>
#include <queue>
#include <cassert>
#include <iostream>
#include <sstream>

#include "../ecs/all_ecs.hpp"

using namespace Core::ECS;

namespace Core {
    namespace Managers {
        // EntityManager manages the creation and destruction of entities
        class EntityManager {
            public:
                EntityManager();
                ~EntityManager();

                std::string ToString() const;

                Entity CreateEntity();
                void DestroyEntity(Entity entity);
                Signature SetSignature(Entity entity, ComponentType componentType);
                Signature GetSignature(Entity entity);

            private:
                // Queue of unused entity IDs
                std::queue<Entity> _availableEntities{};

                // Array of signatures where the index corresponds to the entity ID
                std::array<Signature, MAX_ENTITIES> _signatures{};

                // Total living entities - used to keep limits on how many exist
                Uint32 _livingEntityCount = 0;
        };
    }
}