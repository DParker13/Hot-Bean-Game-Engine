/**
 * @file scene_graph.hpp
 * @author Daniel Parker (DParker13)
 * @brief Scene graph for managing entity hierarchies
 * @version 0.1
 * @date 2026-01-09
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <HotBeanEngine/core/all_core.hpp>

namespace HBE::Default::Utilities {
    using HBE::Core::EntityID;

    /**
     * @brief Manages hierarchical relationships between entities
     *
     * Maintains a level-based scene graph where entities are organized by
     * their depth in the hierarchy. Level 0 contains root entities (no parent),
     * and each subsequent level contains children of the previous levels.
     */
    class SceneGraph {
    private:
        std::unordered_map<EntityID, Uint32> m_entity_graph_level;
        std::map<Uint32, std::set<EntityID>> m_scene_graph;

    public:
        SceneGraph() = default;
        ~SceneGraph() = default;

        /**
         * @brief Add an entity to the scene graph
         * @param entity Entity to add
         * @param parent_entity Parent entity ID (-1 for root entities)
         */
        void AddEntity(EntityID entity, EntityID parent_entity);

        /**
         * @brief Remove an entity from the scene graph
         * @param entity Entity to remove
         */
        void RemoveEntity(EntityID entity);

        /**
         * @brief Update entity's position in the hierarchy
         * @param entity Entity to update
         * @param parent_entity New parent entity ID (-1 for root)
         */
        void UpdateEntity(EntityID entity, EntityID parent_entity);

        /**
         * @brief Get the hierarchical level of an entity
         * @param entity Entity to query
         * @return Level (0 for root, 1+ for children)
         */
        Uint32 GetEntityLevel(EntityID entity) const;

        /**
         * @brief Get all entities at a specific level
         * @param level Level to query
         * @return Set of entities at that level
         */
        const std::set<EntityID> &GetEntitiesAtLevel(Uint32 level) const;

        /**
         * @brief Get all levels in the scene graph
         * @return Map of level to entity sets
         */
        const std::map<Uint32, std::set<EntityID>> &GetAllLevels() const;

        /**
         * @brief Check if an entity exists in the scene graph
         * @param entity Entity to check
         * @return true if entity exists
         */
        bool HasEntity(EntityID entity) const;

        /**
         * @brief Clear the entire scene graph
         */
        void Clear();

    private:
        /**
         * @brief Internal helper to add entity to a specific level
         * @param entity Entity to add
         * @param level Level to add to
         */
        void AddEntityAtLevel(EntityID entity, Uint32 level);
    };
} // namespace HBE::Default::Utilities
