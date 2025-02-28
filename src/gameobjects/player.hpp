#pragma once

#include "gameobject.hpp"

#include "../components/transform-2d.hpp"
#include "../components/controller.hpp"

namespace GameObjects {
    class Player : public GameObject {
    public:
        Player(Core::CoreManager* coreManager);

        Components::Transform2D& GetTransform2D();
        Components::Controller& GetController();
        std::string ToString() const override;
    };
}