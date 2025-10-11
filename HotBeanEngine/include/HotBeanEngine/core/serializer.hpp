#pragma once

#include <HotBeanEngine/core/entity.hpp>

namespace HBE::Core {
    class ISerializer {
        public:
            virtual void Serialize(const std::string& filepath) = 0;
            virtual void Deserialize(const std::string& filepath) = 0;
            virtual bool FileExists(const std::string& filepath) = 0;
    };
}