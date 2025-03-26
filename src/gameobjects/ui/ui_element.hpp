#pragma once

#include <core.hpp>

#include "../../components/transform_2d.hpp"
#include "../../components/texture.hpp"

using namespace Core::ECS;

namespace GameObjects {
    namespace UI {
        template <typename... Cs>
        struct UIElement : public GameObject<Components::Transform2D, Components::Texture, Cs...> {
            UIElement(App& app)
                : GameObject<Components::Transform2D,
                            Components::Texture,
                            Cs...>(app) {};
        };
    }
}