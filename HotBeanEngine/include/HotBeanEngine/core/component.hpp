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

#include <HotBeanEngine/core/iname.hpp>
#include <HotBeanEngine/core/iserializable.hpp>

namespace HBE::Core {
    // ComponentID is an unsigned 64-bit integer
    // This is used to identify a component
    using ComponentID = Uint64;

    /// @brief Base class for all components.
    struct IComponent : public IName, public ISerializable {
        IComponent() = default;
        virtual ~IComponent() = default;

        virtual std::string_view GetName() const override = 0;
        virtual void Serialize(ISerializationWriter &out) const override {};
        virtual void Deserialize(ISerializationReader &in) override {};
    };
} // namespace HBE::Core