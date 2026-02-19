/**
 * @file entity_manager.hpp
 * @author Daniel Parker (DParker13)
 * @brief Manages the creation and destruction of entities.
 * @version 0.1
 * @date 2025-02-23
 *
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <queue>

#include <HotBeanEngine/application/managers/logging_manager.hpp>

namespace HBE::Application::Managers {
    using HBE::Core::ComponentID;
    using HBE::Core::EntityID;
    using HBE::Core::MAX_ENTITIES;
    using HBE::Core::Signature;

    /**
     * @brief Manages entity creation and destruction lifecycle.
     * Handles entity ID allocation, recycling, and signature management.
     * Maintains entity validity and component associations.
     */
    class EntityManager {
    private:
        // Logging manager
        std::shared_ptr<LoggingManager> m_logging_manager;

        // Queue of unused entity IDs
        std::queue<EntityID> m_available_entities;

        std::unordered_map<EntityID, bool> m_alive_entities;

        // Array of signatures where the index corresponds to the entity ID
        std::array<Signature, MAX_ENTITIES> m_signatures;

        // Total living entities - used to keep limits on how many exist
        EntityID m_living_entity_count = 0;

    public:
        EntityManager(std::shared_ptr<LoggingManager> logging_manager);
        ~EntityManager();

        /**
         * @brief Allocate a new entity ID and mark it alive.
         * @return Newly created entity identifier.
         */
        EntityID CreateEntity();

        /**
         * @brief Destroy an entity and recycle its ID.
         * @param entity Entity identifier to destroy.
         */
        void DestroyEntity(EntityID entity);

        /**
         * @brief Destroy every existing entity and reset bookkeeping state.
         */
        void DestroyAllEntities();

        /**
         * @brief Set or clear a bit in an entity signature when a component changes.
         * @param entity Target entity identifier.
         * @param component_id Component bit to toggle.
         * @return Updated signature for the entity.
         */
        Signature SetSignature(EntityID entity, ComponentID component_id);

        /**
         * @brief Explicitly set a component bit in the signature.
         * @param entity Target entity.
         * @param component_id Component bit index.
         * @param value True to set the bit, false to clear it.
         * @return Updated signature.
         */
        Signature SetSignature(EntityID entity, ComponentID component_id, bool value);

        /**
         * @brief Retrieve the signature for an entity.
         * @param entity Entity identifier.
         * @return Const reference to the signature bitset.
         */
        const Signature &GetSignature(EntityID entity) const;

        /**
         * @brief Check whether an entity currently has a component bit set.
         * @param entity Entity identifier.
         * @param component_id Component bit index.
         * @return True if the signature contains the component bit.
         */
        bool HasComponent(EntityID entity, ComponentID component_id);

        /**
         * @brief Get the number of living entities.
         * @return Count of active entities.
         */
        EntityID EntityCount() const;

        /**
         * @brief Get a list of all active entity IDs.
         * @return Vector of living entity identifiers.
         */
        std::vector<EntityID> GetAllEntities();

    private:
        void InitializeEntities();
    };
} // namespace HBE::Application::Managers