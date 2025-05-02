#pragma once

#include <SDL_stdinc.h>
#include <SDL.h>
#include <yaml-cpp/yaml.h>

#include "object.hpp"

namespace Core {
    namespace ECS {
        // ComponentType is an unsigned 32-bit integer
        // This is used to identify a component
        using ComponentType = Uint32;
    
        // Maximum number of components that can be registered
        const ComponentType MAX_COMPONENTS = 64;
    
        struct Component : public Object {
            Component() = default;
            virtual ~Component() = default;

            virtual std::string GetName() const = 0;
            virtual void Serialize(YAML::Emitter& out) const {};
            virtual void Deserialize(YAML::Node& node) {};
        };
    }
}