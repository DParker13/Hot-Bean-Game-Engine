#pragma once

#include "../managers/ecs_manager.hpp"
#include "audio/audio_source.hpp"
#include "input/controller.hpp"
#include "miscellaneous/camera.hpp"
#include "miscellaneous/transform_2d.hpp"
#include "physics/collider_2d.hpp"
#include "physics/rigidbody.hpp"
#include "rendering/shape.hpp"
#include "rendering/texture.hpp"
#include "ui/text.hpp"
#include "ui/ui_element.hpp"

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