#pragma once

#include "../../core/core.hpp"

using namespace Core::ECS;

namespace GameObjects {
    namespace UI {
        template <typename... Cs>
        struct UIElement : public GameObject<Core::Components::Transform2D,
                                            Core::Components::Texture,
                                            Core::Components::UIElement,
                                            Cs...> {
            UIElement()
                : GameObject<Core::Components::Transform2D,
                            Core::Components::Texture,
                            Core::Components::UIElement,
                            Cs...>() {};
        };
    }
}