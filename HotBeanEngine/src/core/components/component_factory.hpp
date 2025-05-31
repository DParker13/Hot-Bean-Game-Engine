#pragma once

#include "../managers/ecs_manager.hpp"
#include "audio_source.hpp"
#include "camera.hpp"
#include "collider_2d.hpp"
#include "controller.hpp"
#include "rigidbody.hpp"
#include "text.hpp"
#include "texture.hpp"
#include "tile.hpp"
#include "transform_2d.hpp"
#include "ui_element.hpp"

namespace Core::Application {
    struct ComponentFactory {
        virtual void RegisterComponents(Core::Managers::ECSManager& ecs_manager);
        static void CreateComponent(Core::Managers::ECSManager& ecs_manager, const std::string& component_name,
                                    YAML::Node node, Entity parent_entity, Entity entity);

        template<typename T>
        static void AddComponent(Core::Managers::ECSManager& ecs_manager, Entity entity, YAML::Node node) {
            static_assert(std::is_base_of_v<Component, T> && "T must inherit from Component!");

            ecs_manager.AddComponent<T>(entity, T());
            ecs_manager.GetComponent<T>(entity).Deserialize(node);
        }
    };
}