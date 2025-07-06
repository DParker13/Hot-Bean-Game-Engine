#pragma once

#include "../application/archetype.hpp"
#include "../components/default_components.hpp"

using namespace Core::Components;

namespace Core::Archetypes {
    using PlayerArchetype = Archetype<Transform2D, Controller, Texture>;
    using CameraArchetype = Archetype<Transform2D, Camera>;
    using UIElementArchetype = Archetype<Transform2D, Texture, UIElement>;
    using TextArchetype = Archetype<Transform2D, Text, UIElement>;
}