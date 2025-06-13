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
    CameraSystem::~CameraSystem() {
        m_active_camera_transform = nullptr;
    };

    void CameraSystem::SetSignature() {
        SETUP_SYSTEM(CameraSystem, Camera, Transform2D);
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

    Transform2D* CameraSystem::GetActiveCameraTransform() {
        return m_active_camera_transform;
    }

    void CameraSystem::FindActiveCamera() {
        bool first_camera_found = false;

        for (auto& entity : m_entities) {
            auto& camera = App::GetInstance().GetECSManager()->GetComponent<Camera>(entity);

            if (camera.m_active) {
                
                if (first_camera_found) {
                    App::GetInstance().Log(LoggingType::WARNING, "More than one camera is active!");
                }

                first_camera_found = true;
                m_active_camera_transform = &App::GetInstance().GetECSManager()->GetComponent<Transform2D>(entity);
                m_active_camera_entity = entity;
            }
        }

        if (!first_camera_found) {
            App::GetInstance().Log(LoggingType::WARNING, "No cameras are active!");
        }

        first_camera_found = false;
    }
}