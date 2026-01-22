/**
 * @file transform_system.cpp
 * @author Daniel Parker
 * @brief System for managing the 2D transformations of game entities.
 * @version 0.1
 * @date 2025-02-18
 * 
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/defaults/systems/rendering/transform_system.hpp>

namespace HBE::Default::Systems {
    TransformSystem::TransformSystem() : ISystem(), m_scene_graph(SceneGraph()) {}

    void TransformSystem::OnEntityAdded(EntityID entity) {
        m_scene_graph.AddEntity(entity, g_ecs.GetComponent<Transform2D>(entity).m_parent);
    }

    void TransformSystem::OnEntityRemoved(EntityID entity) {
        m_scene_graph.RemoveEntity(entity);
    }

    void TransformSystem::OnUpdate() {
        // Iterate through all levels and propagate transforms
        for (auto& level : m_scene_graph.GetAllLevels()) {
            for (auto& entity : level.second) {
                auto& transform = g_ecs.GetComponent<Transform2D>(entity);
                
                // Get parent transform if it exists
                const Transform2D* parent_transform = nullptr;
                if (transform.m_parent != -1) {
                    parent_transform = &g_ecs.GetComponent<Transform2D>(transform.m_parent);
                }
                
                // Propagate transforms
                TransformHelper::PropagateTransforms(transform, parent_transform);
            }
        }
    }
}