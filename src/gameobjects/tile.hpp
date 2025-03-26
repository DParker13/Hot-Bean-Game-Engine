#pragma once

#include <core.hpp>

#include "../components/transform_2d.hpp"
#include "../components/tile.hpp"
#include "../components/rigidbody.hpp"

using namespace Core::ECS;

namespace GameObjects {
    struct Tile : public GameObject<Components::Transform2D, Components::Tile, Components::RigidBody> {

        Tile(App& app)
            : GameObject<Components::Transform2D, Components::Tile, Components::RigidBody>(app) {};
    };
}