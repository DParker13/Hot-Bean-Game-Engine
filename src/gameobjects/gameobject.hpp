#pragma once

#include "../managers/core_manager.hpp"

namespace GameObjects {
    class GameObject {
    public:
        Entity _entity;
        Core::CoreManager* _coreManager;

        GameObject(Core::CoreManager* coreManager);
        virtual ~GameObject() = default;

        Entity GetEntity();
        virtual std::string ToString() const = 0;
    };
}