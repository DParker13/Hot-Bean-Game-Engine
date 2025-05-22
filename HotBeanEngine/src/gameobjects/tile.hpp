#pragma once

#include "../core/core.hpp"

using namespace Core::ECS;

namespace GameObjects {
    struct Tile : public GameObject<Components::Transform2D, Components::Tile> {

        Tile()
            : GameObject<Components::Transform2D, Components::Tile>() {};
    };
}