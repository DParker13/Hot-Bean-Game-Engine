/**
 * @file entity_lifecycle_listener.hpp
 * @author Daniel Parker (DParker13)
 * @brief Interface for objects that need to track entity lifecycle events.
 * @version 0.1
 * @date 2026-02-16
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <HotBeanEngine/core/entity.hpp>

namespace HBE::Application::Managers {
    /**
     * @brief Interface for listening to entity lifecycle events.
     * 
     * Implement this interface to receive notifications when entities gain or lose components.
     * Register with SystemManager via RegisterEntityListener.
     */
    class IEntityLifecycleListener {
    public:
        virtual ~IEntityLifecycleListener() = default;

        /**
         * @brief Called when an entity's component signature changes to match the listener's interest.
         * @param entity The entity ID that gained a component.
         */
        virtual void OnComponentAdded(HBE::Core::EntityID entity) = 0;

        /**
         * @brief Called when an entity's component signature changes to no longer match the listener's interest.
         * @param entity The entity ID that lost a component.
         */
        virtual void OnComponentRemoved(HBE::Core::EntityID entity) = 0;
    };
} // namespace HBE::Application::Managers
