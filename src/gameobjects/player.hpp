#pragma once

#include "gameobject.hpp"

#include "../components/transform.hpp"
#include "../components/player.hpp"

namespace GameObjects {
    class Player : public GameObject {
    public:
        Player(Core::CoreManager* coreManager);

        Components::Transform& GetTransform();
        Components::Player& GetPlayer();
        std::string ToString() const override;
    };
}