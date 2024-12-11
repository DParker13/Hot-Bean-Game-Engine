#pragma once

#include <SDL_stdinc.h>
#include <array>
#include <queue>
#include <cassert>
#include <iostream>

#include "ecs.hpp"

namespace Core {
    // EntityManager manages the creation and destruction of entities
    class EntityManager {
        public:
            EntityManager();
            ~EntityManager();

            void Print() const;

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
            Uint32 _livingEntityCount{};
    };
}