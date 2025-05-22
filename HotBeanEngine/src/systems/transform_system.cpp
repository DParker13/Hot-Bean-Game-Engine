#include "transform_system.hpp"

namespace Systems {
    TransformSystem::TransformSystem(CameraSystem& camera_system)
        : System(), m_camera_system(camera_system) {}

    void TransformSystem::SetSignature() {
        SETUP_SYSTEM(TransformSystem, Transform2D);
    }

    void TransformSystem::OnUpdate() {
        for (auto& entity : m_entities) {
            // Don't transform the camera
            if (App::GetInstance().GetECSManager()->HasComponentType<Camera>(entity)) {
                continue;
            }

            auto& transform = App::GetInstance().GetECSManager()->GetComponent<Transform2D>(entity);
            auto* camera_transform = m_camera_system.GetActiveCameraTransform();

            if (camera_transform) {
                transform.m_screen_position.x = transform.m_world_position.x - camera_transform->m_world_position.x;
                transform.m_screen_position.y = transform.m_world_position.y - camera_transform->m_world_position.y;
            }
        }
    }
}