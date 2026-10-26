/**
 * @file iserializer.hpp
 * @author Daniel Parker (DParker13)
 * @brief Abstract interface for serialization.
 * @version 0.1
 * @date 2026-06-19
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <filesystem>

#include <HotBeanEngine/core/iname.hpp>
#include <HotBeanEngine/core/iserializable.hpp>

namespace HBE::Core {
    struct ISerializer {
        virtual ~ISerializer() = default;

        virtual void Serialize(std::filesystem::path filepath, Core::ISerializable &object, bool append = false) = 0;
        virtual void Deserialize(std::filesystem::path filepath, Core::ISerializable &object) = 0;
        virtual bool FileExists(std::filesystem::path filepath) { return std::filesystem::exists(filepath); }
    };
} // namespace HBE::Core
