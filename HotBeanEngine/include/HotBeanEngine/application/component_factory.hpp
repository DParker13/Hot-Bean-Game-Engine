#pragma once

#include <HotBeanEngine/application/managers/ecs_manager.hpp>

namespace HBE::Application {
    class IComponentFactory {
        public:
            virtual void RegisterComponents() = 0;
            virtual void CreateComponentFromYAML(const std::string& component_name,
                                                YAML::Node node, Entity parent_entity, Entity entity) = 0;

            void SetECSManager(std::shared_ptr<Managers::ECSManager> ecs_manager) {
                m_ecs_manager = ecs_manager;
            }

            template<typename T>
            void AddComponent(Entity entity, YAML::Node node) {
                static_assert(std::is_base_of_v<Component, T> && "T must inherit from Component");

                m_ecs_manager->AddComponent<T>(entity, T());
                m_ecs_manager->GetComponent<T>(entity).Deserialize(node);
            }

            template<typename T, typename... Args>
            void AddComponent(Entity entity, YAML::Node node, Args... args) {
                static_assert(std::is_base_of_v<Component, T> && "T must inherit from Component");

                m_ecs_manager->AddComponent<T>(entity, T(args...));
                m_ecs_manager->GetComponent<T>(entity).Deserialize(node);
            }

        protected:
            std::shared_ptr<Managers::ECSManager> m_ecs_manager;
    };
}