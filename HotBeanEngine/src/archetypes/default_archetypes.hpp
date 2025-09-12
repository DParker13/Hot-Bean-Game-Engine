#pragma once

#include "archetype.hpp"
#include "../components/default_components.hpp"

using namespace HBE::Components;

namespace HBE::Archetypes {
    using PlayerArchetype = Archetype<Transform2D, Controller, Texture>;
    using CameraArchetype = Archetype<Transform2D, Camera>;
    using TextureArchetype = Archetype<Transform2D, Texture>;
    using ShapeArchetype = Archetype<Transform2D, Texture, Shape>;

    // --- UI ---
    using UIElementArchetype = Archetype<Transform2D, Texture, UIElement>;
    using TextArchetype = Archetype<Transform2D, Text, Texture, UIElement>;
}