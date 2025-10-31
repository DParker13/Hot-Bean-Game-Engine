/**
 * @file camera_system.cpp
 * @author Daniel Parker (DParker13)
 * @brief System for offsetting all transforms based on the active camera. Only one camera can be active at a time.
 * @version 0.1
 * @date 2025-05-14
 * 
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/defaults/systems/rendering/camera_system.hpp>

using namespace HBE::Default::Components;

namespace HBE::Default::Systems {
    void CameraSystem::OnStart() {
        FindActiveCamera();
    }

    void CameraSystem::OnUpdate() {
        Camera camera = g_ecs.GetComponent<Camera>(m_active_camera_entity);

        if (!camera.m_active) {
            FindActiveCamera();
        }
    }

    Entity CameraSystem::GetActiveCameraEntity() {
        return m_active_camera_entity;
    }

    void CameraSystem::FindActiveCamera() {
        bool first_camera_found = false;

        for (auto& entity : m_entities) {
            auto& camera = g_ecs.GetComponent<Camera>(entity);

            if (camera.m_active) {
                
                if (first_camera_found) {
                    LOG(LoggingType::WARNING, "More than one camera is active!");
                }

                first_camera_found = true;
                m_active_camera_entity = static_cast<Sint64>(entity);
            }
        }

        if (!first_camera_found) {
            LOG(LoggingType::WARNING, "No cameras are active!");
        }

        first_camera_found = false;
    }

    glm::vec2 CameraSystem::CalculateScreenPosition(const glm::vec2& world_position) {
        Entity camera_entity = GetActiveCameraEntity();
        Transform2D camera_transform = g_ecs.GetComponent<Transform2D>(camera_entity);
        glm::vec2 screen_position = world_position - camera_transform.m_world_position;

        return screen_position;
    }
}