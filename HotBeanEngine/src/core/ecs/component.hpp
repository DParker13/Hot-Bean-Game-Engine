#pragma once

#include <SDL_stdinc.h>
#include <SDL.h>
#include <yaml-cpp/yaml.h>

namespace Core {
    namespace ECS {
        // ComponentType is an unsigned 32-bit integer
        // This is used to identify a component
        using ComponentType = Uint32;
    
        struct Component {
            Component() = default;
            virtual ~Component() = default;

            virtual std::string GetName() const = 0;
            virtual void Serialize(YAML::Emitter& out) const {};
            virtual void Deserialize(YAML::Node& node) {};
        };
    }
}