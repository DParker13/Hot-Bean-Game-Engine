#pragma once

#include "../ecs_manager.hpp"

namespace Core::Managers::Helpers {
    struct ComponentRegister {
        virtual void RegisterComponents();

        static void CreateComponent(ECSManager& ecs_manager, const std::string& component_name,
                                    YAML::Node node, Entity entity);
    
        template<typename T>
        static void AddComponent(ECSManager& ecs_manager, Entity entity, YAML::Node node) {
            static_assert(std::is_base_of_v<Component, T> && "T must inherit from Component!");

            ecs_manager.AddComponent<T>(entity, T());
            ecs_manager.GetComponent<T>(entity).Deserialize(node);
        }
    };
}