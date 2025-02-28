#pragma once

#include "gameobject.hpp"

#include "../components/transform-2d.hpp"
#include "../components/tile.hpp"

namespace GameObjects {
    class Tile : public GameObject {
    public:
        Tile(Core::CoreManager* coreManager);

        Components::Transform2D& GetTransform2D();
        Components::Tile& GetTile();
        std::string ToString() const override;
    };
}