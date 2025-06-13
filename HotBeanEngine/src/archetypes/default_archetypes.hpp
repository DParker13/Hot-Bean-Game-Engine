#pragma once

#include "../core/core.hpp"

namespace Archetypes {
    using PlayerArchetype = Archetype<Transform2D, Controller, Texture, Collider2D>;
    using CameraArchetype = Archetype<Camera, Transform2D>;
    using UIElementArchetype = Archetype<Transform2D, Texture, UIElement>;
    using TextArchetype = Archetype<Text, Transform2D, UIElement>;
}