#pragma once

#include "../../application/all_application.hpp"

using namespace Core::Components;
using namespace Core::Application;
using namespace Core::ECS;

namespace Core::Systems {
    class CameraSystem : public System {
        public:
            CameraSystem() = default;

            void SetSignature() override;
            void OnStart() override;
            void OnUpdate() override;

            Entity GetActiveCameraEntity();

        private:
            Entity m_active_camera_entity;

            void FindActiveCamera();
    };
}