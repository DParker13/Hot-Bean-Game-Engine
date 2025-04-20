#pragma once

#include "../../core/core.hpp"

#include "../../components/transform_2d.hpp"
#include "../../components/texture.hpp"

using namespace Core::ECS;

namespace GameObjects {
    namespace UI {
        template <typename... Cs>
        struct UIElement : public GameObject<Components::Transform2D,
                                            Components::Texture,
                                            Components::UIElement,
                                            Cs...> {
            UIElement()
                : GameObject<Components::Transform2D,
                            Components::Texture,
                            Components::UIElement,
                            Cs...>() {};
        };
    }
}