#pragma once

#include <string>

namespace Core {
    namespace ECS {
        struct Object {
            virtual std::string ToString() const = 0;
        };
    }
}