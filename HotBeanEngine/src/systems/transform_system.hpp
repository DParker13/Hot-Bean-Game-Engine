#pragma once

#include "../core/core.hpp"

#include "camera_system.hpp"

using namespace Core::Application;
using namespace Core::ECS;

namespace Systems {
    class TransformSystem : public System {
        public:
            TransformSystem(CameraSystem& camera_system);

            void SetSignature() override;
            void OnUpdate() override;
        private:
            CameraSystem& m_camera_system;
    };
}