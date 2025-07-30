/**
 * @file camera_system.cpp
 * @author Daniel Parker (DParker13)
 * @brief Camera system. Only one camera can be active at a time.
 * @version 0.1
 * @date 2025-05-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "camera_system.hpp"

using namespace Core::Components;

namespace Core::Systems {

    void CameraSystem::SetSignature() {
        SETUP_SYSTEM(CameraSystem, Transform2D, Camera);
    }

    void CameraSystem::OnStart() {
        FindActiveCamera();
    }

    void CameraSystem::OnUpdate() {
        Camera camera = App::GetInstance().GetComponent<Camera>(m_active_camera_entity);

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
            auto& camera = App::GetInstance().GetECSManager()->GetComponent<Camera>(entity);

            if (camera.m_active) {
                
                if (first_camera_found) {
                    LOG(LoggingType::WARNING, "More than one camera is active!");
                }

                first_camera_found = true;
                m_active_camera_entity = entity;
            }
        }

        if (!first_camera_found) {
            LOG(LoggingType::WARNING, "No cameras are active!");
        }

        first_camera_found = false;
    }
}