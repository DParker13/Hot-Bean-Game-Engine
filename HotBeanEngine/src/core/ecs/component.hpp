#pragma once

#include <SDL_stdinc.h>
#include <SDL.h>

#include "object.hpp"

namespace Core {
    namespace ECS {
        // ComponentType is an unsigned 32-bit integer
        // This is used to identify a component
        using ComponentType = Uint32;
    
        // Maximum number of components that can be registered
        const ComponentType MAX_COMPONENTS = 64;
    
        struct Component : public Object {
            std::string _name;

            Component() = default;
            virtual ~Component() = default;
        };
    }
}