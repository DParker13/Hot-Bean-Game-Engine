#pragma once

#include <SDL_stdinc.h>
#include <SDL.h>

namespace Core::ECS {
    // Entity is an unsigned 32-bit integer
    // This is used to identify an entity
    using Entity = Uint32;

    const Entity MAX_ENTITIES = 5000;
}