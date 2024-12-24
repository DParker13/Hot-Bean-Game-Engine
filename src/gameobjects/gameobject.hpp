#pragma once

#include "../managers/core_manager.hpp"

namespace GameObjects {
    class GameObject {
    public:
        Entity entity;
        Core::CoreManager* coreManager;

        GameObject(Core::CoreManager* coreManager);
        virtual ~GameObject() = default;
        virtual std::string ToString() const = 0;
    };
}