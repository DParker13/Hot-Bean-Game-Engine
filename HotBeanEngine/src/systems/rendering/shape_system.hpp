#pragma once

#include "../../application/all_application.hpp"
#include "camera_system.hpp"

using namespace HBE::Components;
using namespace HBE::Application;
using namespace HBE::Core;

namespace Systems {
    class ShapeSystem : public System {
        private:
            CameraSystem& m_camera_system;

        public:
            DEFINE_SIGNATURE(ShapeSystem, Transform2D, Texture, Shape);
            ShapeSystem(CameraSystem& camera_system) : System(), m_camera_system(camera_system) {}

            void OnRender() override;
            void OnEntityAdded(Entity entity) override;

        private:
            void CreateTextureForEntity(Entity entity);
    };
}