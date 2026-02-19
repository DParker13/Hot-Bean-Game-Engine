/**
 * @file default_archetypes.hpp
 * @author Daniel Parker (DParker13)
 * @brief Default archetype definitions. Combines components into archetypes for easier entity creation.
 * @version 0.1
 * @date 2025-07-06
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <HotBeanEngine/application/archetype.hpp>
#include <HotBeanEngine/defaults/components/default_components.hpp>

namespace HBE::Default::Archetypes {
    using HBE::Application::Archetype;
    using HBE::Default::Components::Transform2D;
    using HBE::Default::Components::Controller;
    using HBE::Default::Components::Texture;
    using HBE::Default::Components::Camera;
    using HBE::Default::Components::Shape;
    using HBE::Default::Components::UIElement;
    using HBE::Default::Components::Text;

    using PlayerArchetype = Archetype<Transform2D, Controller, Texture>;
    using CameraArchetype = Archetype<Transform2D, Camera>;
    using TextureArchetype = Archetype<Transform2D, Texture>;
    using ShapeArchetype = Archetype<Transform2D, Texture, Shape>;

    // --- UI ---
    using UIElementArchetype = Archetype<Transform2D, Texture, UIElement>;
    using TextArchetype = Archetype<Transform2D, Text, Texture, UIElement>;
} // namespace HBE::Default::Archetypes