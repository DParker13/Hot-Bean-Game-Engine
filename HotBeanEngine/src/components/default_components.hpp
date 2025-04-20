#pragma once

#include "../core/core.hpp"

#include "audio_source.hpp"
#include "collider_2d.hpp"
#include "controller.hpp"
#include "rigidbody.hpp"
#include "text.hpp"
#include "texture.hpp"
#include "tile.hpp"
#include "transform_2d.hpp"
#include "ui_element.hpp"

namespace Components {
    class DefaultComponents {
    public:
        static void RegisterComponents(std::shared_ptr<ECSManager> ecsManager) {
            ecsManager->RegisterComponentType<AudioSource>();
            ecsManager->RegisterComponentType<Collider2D>();
            ecsManager->RegisterComponentType<Controller>();
            ecsManager->RegisterComponentType<RigidBody>();
            ecsManager->RegisterComponentType<Text>();
            ecsManager->RegisterComponentType<Texture>();
            ecsManager->RegisterComponentType<Tile>();
            ecsManager->RegisterComponentType<Transform2D>();
            ecsManager->RegisterComponentType<UIElement>();
        }
    };
}