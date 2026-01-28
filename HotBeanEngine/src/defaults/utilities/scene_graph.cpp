/**
 * @file scene_graph.cpp
 * @author Daniel Parker (DParker13)
 * @brief Implementation of scene graph for entity hierarchies
 * @version 0.1
 * @date 2026-01-09
 *
 * @copyright Copyright (c) 2026
 */

#include <HotBeanEngine/defaults/utilities/scene_graph.hpp>

namespace HBE::Default::Utilities {
    void SceneGraph::AddEntity(EntityID entity, EntityID parent_entity) {
        // Update parent levels first
        if (parent_entity != -1) {
            // Ensure parent is in graph
            if (!HasEntity(parent_entity)) {
                // Parent needs to be added first - this shouldn't happen in normal usage
                return;
            }

            // Add entity at parent level + 1
            Uint32 parent_level = m_entity_graph_level[parent_entity];
            AddEntityAtLevel(entity, parent_level + 1);
        } else {
            // Root level entity
            AddEntityAtLevel(entity, 0);
        }
    }

    void SceneGraph::RemoveEntity(EntityID entity) {
        if (!HasEntity(entity)) {
            return;
        }

        Uint32 level = m_entity_graph_level[entity];

        // Remove from scene graph level
        m_scene_graph[level].erase(entity);

        // Remove empty level
        if (m_scene_graph[level].empty()) {
            m_scene_graph.erase(level);
        }

        // Remove from entity level map
        m_entity_graph_level.erase(entity);
    }

    void SceneGraph::UpdateEntity(EntityID entity, EntityID parent_entity) {
        // Remove and re-add to update level
        RemoveEntity(entity);
        AddEntity(entity, parent_entity);
    }

    Uint32 SceneGraph::GetEntityLevel(EntityID entity) const {
        auto it = m_entity_graph_level.find(entity);
        return (it != m_entity_graph_level.end()) ? it->second : 0;
    }

    const std::set<EntityID> &SceneGraph::GetEntitiesAtLevel(Uint32 level) const {
        static const std::set<EntityID> empty_set;
        auto it = m_scene_graph.find(level);
        return (it != m_scene_graph.end()) ? it->second : empty_set;
    }

    const std::map<Uint32, std::set<EntityID>> &SceneGraph::GetAllLevels() const { return m_scene_graph; }

    bool SceneGraph::HasEntity(EntityID entity) const {
        return m_entity_graph_level.find(entity) != m_entity_graph_level.end();
    }

    void SceneGraph::Clear() {
        m_scene_graph.clear();
        m_entity_graph_level.clear();
    }

    void SceneGraph::AddEntityAtLevel(EntityID entity, Uint32 level) {
        // Check if the current entity is already mapped to a level
        if (m_entity_graph_level.find(entity) == m_entity_graph_level.end()) {
            m_entity_graph_level.emplace(entity, level);
        } else {
            // Update existing mapping
            m_entity_graph_level[entity] = level;
        }

        // Check if the current scene graph level exists
        if (m_scene_graph.find(level) == m_scene_graph.end()) {
            m_scene_graph.emplace(level, std::set<EntityID>{entity});
        } else if (m_scene_graph[level].find(entity) == m_scene_graph[level].end()) {
            m_scene_graph[level].emplace(entity);
        }
    }
} // namespace HBE::Default::Utilities
