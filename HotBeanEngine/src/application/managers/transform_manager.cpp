#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/application/managers/transform_manager.hpp>

namespace HBE::Application::Managers {
    void TransformManager::OnUpdate() {

        // If not playing, also propagate transforms for editor camera to ensure it moves properly in the editor
        if (!g_app.GetLoopManager().IsState(ApplicationState::Playing)) {
            PropagateTransforms(g_app.GetEditorGUI().GetEditorCameraTransform(), nullptr);
        }

        // Iterate through all levels and propagate transforms
        for (auto &level : m_scene_graph.GetAllLevels()) {
            for (auto &entity : level.second) {
                auto &transform = g_ecs.GetComponent<Transform2D>(entity);

                // Get parent transform if it exists
                const Transform2D *parent_transform = nullptr;
                if (transform.m_parent != -1) {
                    parent_transform = &g_ecs.GetComponent<Transform2D>(transform.m_parent);
                }

                // Propagate transforms
                PropagateTransforms(transform, parent_transform);
            }
        }
    }

    /**
     * @brief Propagate world-space transforms from parent to child
     * @param transform Transform to update
     * @param parent_transform Parent transform (nullptr if root)
     */
    void TransformManager::PropagateTransforms(Transform2D &transform, const Transform2D *parent_transform) {
        // Convert local position to world position based on parent
        if (transform.m_parent != -1 && parent_transform != nullptr) {
            transform.m_world_position = parent_transform->m_world_position + transform.m_local_position;
            transform.m_world_rotation = parent_transform->m_world_rotation + transform.m_local_rotation;
        }
        else {
            transform.m_world_position = transform.m_local_position;
            transform.m_world_rotation = transform.m_local_rotation;
        }
    }
} // namespace HBE::Application::Managers