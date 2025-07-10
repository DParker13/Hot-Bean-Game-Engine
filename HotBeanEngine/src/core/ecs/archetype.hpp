#pragma once

#include <vector>
#include <string>

namespace Core::ECS {
    struct IArchetype {
        virtual std::vector<std::string> GetComponentNames() = 0;
    };
}