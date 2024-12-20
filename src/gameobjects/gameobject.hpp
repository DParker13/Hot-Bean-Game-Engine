#pragma once

#include "../core/ecs.hpp"
#include "../managers/core_manager.hpp"

namespace GameObjects {
    class IGameObject {
    public:
        virtual ~IGameObject() = default;
        virtual std::string ToString(Core::CoreManager& coreManager) const = 0;
    };
}