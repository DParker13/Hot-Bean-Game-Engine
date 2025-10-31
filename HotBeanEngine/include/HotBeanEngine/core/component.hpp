/**
 * @file component.hpp
 * @author Daniel Parker (DParker13)
 * @brief Component base class.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <SDL3/SDL.h>
#include <yaml-cpp/yaml.h>

#include <HotBeanEngine/core/iname.hpp>

namespace HBE::Core {
    // ComponentType is an unsigned 32-bit integer
    // This is used to identify a component
    using ComponentType = Uint32;

    /// @brief Base class for all components.
    struct Component : public IName {
        Component() = default;
        virtual ~Component() = default;
        
        virtual std::string_view GetName() const = 0;
        virtual void Serialize(YAML::Emitter& out) const {};
        virtual void Deserialize(YAML::Node& node) {};
    };
}