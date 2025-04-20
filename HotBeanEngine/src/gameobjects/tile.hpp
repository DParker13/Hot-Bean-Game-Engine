#pragma once

#include "../core/core.hpp"

#include "../components/transform_2d.hpp"
#include "../components/tile.hpp"
#include "../components/rigidbody.hpp"

using namespace Core::ECS;

namespace GameObjects {
    struct Tile : public GameObject<Components::Transform2D, Components::Tile, Components::RigidBody> {

        Tile()
            : GameObject<Components::Transform2D, Components::Tile, Components::RigidBody>() {};
    };
}