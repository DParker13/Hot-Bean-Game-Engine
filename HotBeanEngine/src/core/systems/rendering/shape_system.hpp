#pragma once

#include "../../application/all_application.hpp"

using namespace Core::Components;
using namespace Core::Application;
using namespace Core::ECS;

namespace Core::Systems {
    class ShapeSystem : public System {
        public:
            ShapeSystem() = default;

            void SetSignature() override;
            void OnRender() override;
            void OnEntityAdded(Entity entity) override;

        private:
            void CreateTextureForEntity(Entity entity);
            void LayoutVertices(Entity entity);
    };
}