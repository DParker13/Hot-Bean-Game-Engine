#pragma once

#include <SDL_stdinc.h>
#include <SDL.h>

namespace Core::ECS {
    // Entity is a signed 32-bit integer
    // This is used to identify an entity
    using Entity = Sint32;
}