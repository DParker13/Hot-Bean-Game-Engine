/**
 * @file iserializable.hpp
 * @author Daniel Parker (DParker13)
 * @brief Interface for serialization and deserialization.
 * @version 0.1
 * @date 2025-10-11
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <HotBeanEngine/core/iserialization_reader.hpp>
#include <HotBeanEngine/core/iserialization_writer.hpp>

namespace HBE::Core {
    /**
     * @brief Interface for general serialization.
     */
    class ISerializable {
    public:
        virtual void Serialize(ISerializationWriter &out) const = 0;
        virtual void Deserialize(ISerializationReader &in) = 0;
    };
} // namespace HBE::Core