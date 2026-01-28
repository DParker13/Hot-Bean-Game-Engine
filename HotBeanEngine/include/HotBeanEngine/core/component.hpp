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
    // ComponentID is an unsigned 64-bit integer
    // This is used to identify a component
    using ComponentID = Uint64;

    /// @brief Base class for all components.
    struct IComponent : public IName {
        IComponent() = default;
        virtual ~IComponent() = default;

        virtual std::string_view GetName() const = 0;
        virtual void Serialize(YAML::Emitter &out) const {};
        virtual void Deserialize(YAML::Node &node) {};
    };
} // namespace HBE::Core