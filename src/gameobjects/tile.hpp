#pragma once

#include "gameobject.hpp"

#include "../components/transform.hpp"
#include "../components/tile.hpp"

namespace GameObjects {
    class Tile : public GameObject {
    public:
        Tile(Core::CoreManager* coreManager);

        Components::Transform& GetTransform();
        Components::Tile& GetTile();
        std::string ToString() const override;
    };
}