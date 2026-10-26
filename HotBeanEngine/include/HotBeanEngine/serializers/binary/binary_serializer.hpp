/**
 * @file binary_serializer.hpp
 * @brief Generic serializer for flat binary-serialized objects.
 */

#pragma once

#include <filesystem>

#include <HotBeanEngine/core/iserializer.hpp>

namespace HBE::Serializers {
    class BinarySerializer : public Core::ISerializer {
    public:
        void Serialize(std::filesystem::path filepath, Core::ISerializable &object, bool append = false) override;
        void Deserialize(std::filesystem::path filepath, Core::ISerializable &object) override;
    };
} // namespace HBE::Serializers