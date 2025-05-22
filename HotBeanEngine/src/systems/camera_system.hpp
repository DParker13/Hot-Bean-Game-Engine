#pragma once

#include "../core/core.hpp"

using namespace Components;
using namespace Core::Application;
using namespace Core::ECS;

namespace Systems {
    class CameraSystem : public System {
        public:
            CameraSystem() = default;
            ~CameraSystem();

            void SetSignature() override;            
            void OnEvent(SDL_Event& event) override;
            void OnUpdate() override;

            Transform2D* GetActiveCameraTransform();

        private:
            Transform2D* m_active_camera_transform;
    };
}