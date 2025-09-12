#include "transform_system.hpp"

namespace Systems {
    TransformSystem::TransformSystem(CameraSystem& camera_system)
        : System(), m_camera_system(camera_system) {}

    void TransformSystem::OnEntityAdded(Entity entity) {
        UpdateSceneGraph(entity);
    }

    void TransformSystem::OnEntityRemoved(Entity entity) {
        // TODO: Reorganize scene graph when child's parent is removed
        // Might just make sense to use a more formal tree/graph structure
        m_scene_graph[m_entity_graph_level[entity]].erase(entity);
        m_entity_graph_level.erase(entity);
    }

    void TransformSystem::OnUpdate() {
        Entity camera_entity = m_camera_system.GetActiveCameraEntity();
        Transform2D camera_transform = g_ecs.GetComponent<Transform2D>(camera_entity);

        for (auto& level : m_scene_graph) {
            for (auto& entity : level.second) {
                auto& transform = g_ecs.GetComponent<Transform2D>(entity);

                // Convert local position to world position based on parent
                if (transform.m_parent != -1) {
                    auto& parent_transform = g_ecs.GetComponent<Transform2D>(transform.m_parent);

                    transform.m_world_position.x = parent_transform.m_world_position.x + transform.m_local_position.x;
                    transform.m_world_position.y = parent_transform.m_world_position.y + transform.m_local_position.y;
                }

                // Convert world position to screen position (ignoring active camera)
                if (entity != camera_entity) {
                    transform.m_screen_position.x = transform.m_world_position.x - camera_transform.m_world_position.x;
                    transform.m_screen_position.y = transform.m_world_position.y - camera_transform.m_world_position.y;
                }
            }
        }
    }

    void TransformSystem::UpdateSceneGraph(Entity entity) {
        Entity parent_entity = g_ecs.GetComponent<Transform2D>(entity).m_parent;

        // Update parent levels first
        if (parent_entity != -1) {
            // Recursively update scene graph parents
            UpdateSceneGraph(parent_entity);

            // Update scene graph child level
            UpdateEntityInSceneGraph(entity, m_entity_graph_level[parent_entity] + 1);
        }
        else {
            // Update scene graph root level
            UpdateEntityInSceneGraph(entity, 0);
        }
        
    }

    void TransformSystem::UpdateEntityInSceneGraph(Entity entity, int level) {
        // Check if the current entity is already mapped to a level
        if (m_entity_graph_level.find(entity) == m_entity_graph_level.end()) {
            m_entity_graph_level.emplace(entity, level);
        }

        // Check if the current scene graph level exists
        if (m_scene_graph.find(level) == m_scene_graph.end()) {
            m_scene_graph.emplace(level, std::set<Entity>{ entity });
        }
        else if (m_scene_graph[level].find(entity) == m_scene_graph[level].end()) {
            m_scene_graph[level].emplace(entity);
        }    
    }
}