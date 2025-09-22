#pragma once

#include "../../application/all_application.hpp"

using namespace HBE::Components;
using namespace HBE::Application;
using namespace HBE::Core;

namespace Systems {
    class CameraSystem : public System {
        private:
            Entity m_active_camera_entity;

        public:
            DEFINE_SIGNATURE(CameraSystem, Transform2D, Camera);
            CameraSystem() = default;

            void OnStart() override;
            void OnUpdate() override;

            Entity GetActiveCameraEntity();
            glm::vec2 CalculateScreenPosition(const glm::vec2& world_position);

        private:
            void FindActiveCamera();
    };
}