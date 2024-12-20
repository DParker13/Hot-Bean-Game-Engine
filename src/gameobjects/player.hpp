#pragma once

#include "gameobject.hpp"

#include "../components/transform.hpp"
#include "../components/player.hpp"

namespace GameObjects {
    class Player : public IGameObject {
    public:
        Entity entity;
        Core::CoreManager* coreManager;

        Player(Core::CoreManager* coreManager);

        Components::Transform& GetTransform();
        Components::Player& GetPlayer();
        std::string ToString(Core::CoreManager& coreManager) const override;
    };
}