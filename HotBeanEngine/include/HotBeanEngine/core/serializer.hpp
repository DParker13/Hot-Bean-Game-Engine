/**
 * @file serializer.hpp
 * @author Daniel Parker (DParker13)
 * @brief Interface for serialization and deserialization.
 * @version 0.1
 * @date 2025-10-11
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

namespace HBE::Core {
    /**
     * @brief Interface for general serialization.
     */
    class ISerializer {
    public:
        virtual void Serialize(std::string_view filepath) = 0;
        virtual void Deserialize(std::string_view filepath) = 0;
        virtual bool FileExists(std::string_view filepath) = 0;
    };
} // namespace HBE::Core