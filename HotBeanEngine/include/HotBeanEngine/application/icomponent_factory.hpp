/**
 * @file icomponent_factory.hpp
 * @author Daniel Parker (DParker13)
 * @brief Component factory interface for creating and registering components.
 * @version 0.1
 * @date 2025-05-12
 *
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <HotBeanEngine/application/managers/ecs_manager.hpp>
#include <HotBeanEngine/core/icomponent_serializer.hpp>

namespace HBE::Application {
    using Core::EntityID;

    /**
     * @brief Interface for creating and registering components.
     * Provides methods for component registration and format-agnostic deserialization.
     */
    class IComponentFactory {
    protected:
        std::shared_ptr<Managers::ECSManager> m_ecs_manager;

    public:
        virtual void RegisterComponents() = 0;
        virtual void CreateComponent(const std::string &component_name, Core::IComponentReader &reader,
                                     EntityID parent_entity, EntityID entity) = 0;

        void SetECSManager(std::shared_ptr<Managers::ECSManager> ecs_manager) { m_ecs_manager = ecs_manager; }

        template <typename T, typename... Args>
        void AddComponent(EntityID entity, Core::IComponentReader &reader, const Args &...args) {
            static_assert(std::is_base_of_v<Core::IComponent, T> && "T must inherit from IComponent");

            m_ecs_manager->AddComponent<T>(entity, T(args...));
            m_ecs_manager->GetComponent<T>(entity).Deserialize(reader);
        }
    };
} // namespace HBE::Application