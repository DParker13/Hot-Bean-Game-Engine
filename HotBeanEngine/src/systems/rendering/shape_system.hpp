#pragma once

#include "../../application/all_application.hpp"

using namespace HBE::Components;
using namespace HBE::Application;
using namespace HBE::Core;

namespace Systems {
    class ShapeSystem : public System {
        public:
            DEFINE_SIGNATURE(ShapeSystem, Transform2D, Texture, Shape);
            ShapeSystem() = default;

            void OnRender() override;
            void OnEntityAdded(Entity entity) override;

        private:
            void CreateTextureForEntity(Entity entity);
    };
}