#pragma once

#include <vector>
#include <string>

namespace HBE::Core {
    struct IArchetype {
        virtual std::vector<std::string> GetComponentNames() = 0;
    };
}