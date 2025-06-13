#pragma once

#include "../../application/all_application.hpp"

using namespace Core::Components;
using namespace Core::Application;
using namespace Core::ECS;

namespace Core::Systems {
    class CameraSystem : public System {
        public:
            CameraSystem() = default;
            ~CameraSystem();

            void SetSignature() override;
            void OnStart() override;
            void OnUpdate() override;

            Transform2D* GetActiveCameraTransform();

        private:
            Entity m_active_camera_entity;
            Transform2D* m_active_camera_transform;

            void FindActiveCamera();
    };
}