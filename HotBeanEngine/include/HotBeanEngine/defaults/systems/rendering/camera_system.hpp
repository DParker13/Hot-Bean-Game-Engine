#pragma once

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/defaults/components/default_components.hpp>

using namespace HBE::Default::Components;
using namespace HBE::Application;
using namespace HBE::Core;

namespace HBE::Default::Systems {
    class CameraSystem : public System {
        private:
            Entity m_active_camera_entity = -1;

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