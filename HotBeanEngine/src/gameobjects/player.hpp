#pragma once

#include "../core/core.hpp"

#include "../components/transform_2d.hpp"
#include "../components/controller.hpp"
#include "../components/texture.hpp"
#include "../components/collider_2d.hpp"

namespace GameObjects {
    struct Player : public GameObject<Components::Transform2D,
                                    Components::Controller,
                                    Components::Texture,
                                    Components::Collider2D> {

        Player()
            : GameObject<Components::Transform2D,
                        Components::Controller,
                        Components::Texture,
                        Components::Collider2D>() {};
    };
}