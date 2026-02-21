/**
 * @file component_listener.hpp
 * @author Daniel Parker (DParker13)
 * @brief Interface for objects that need to track entity lifecycle events.
 * @version 0.1
 * @date 2026-02-16
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <HotBeanEngine/core/all_core.hpp>
#include <unordered_set>

namespace HBE::Application::Managers {
    /**
     * @brief Base class for listening to component changes on entities.
     *
     * Implement this base class to receive notifications when entities gain or lose components.
     * Register with ECSManager via RegisterComponentListener.
     */
    class ComponentListener {
    private:
        std::unordered_set<HBE::Core::ComponentID> m_listened_components =
            {}; ///< Set of component IDs this listener is interested in

    public:
        ~ComponentListener() = default;

        /**
         * @brief Sets the set of component IDs this listener is interested in.
         * @param component_ids Set of ComponentIDs to filter for.
         */
        void ListenForComponents(const std::unordered_set<HBE::Core::ComponentID> &component_ids) {
            m_listened_components = component_ids;
        }

        const std::unordered_set<HBE::Core::ComponentID> &GetListenedComponents() const {
            return m_listened_components;
        }

        /**
         * @brief Called when an entity's component signature changes to match the listener's interest.
         * @param entity The entity ID that gained a component.
         */
        virtual void OnComponentAdded(HBE::Core::IComponent *component, HBE::Core::EntityID entity) = 0;

        /**
         * @brief Called when an entity's component signature changes to no longer match the listener's interest.
         * @param entity The entity ID that lost a component.
         */
        virtual void OnComponentRemoved(HBE::Core::EntityID entity) = 0;
    };
} // namespace HBE::Application::Managers
