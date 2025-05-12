#pragma once

#include "../core/core.hpp"

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