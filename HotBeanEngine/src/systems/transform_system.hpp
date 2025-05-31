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
            void OnEntityAdded(Entity entity) override;
            void OnEntityRemoved(Entity entity) override;
            void OnUpdate() override;
        private:
            CameraSystem& m_camera_system;
            std::unordered_map<Entity, Uint32> m_entity_graph_level;
            std::map<Uint32, std::set<Entity>> m_scene_graph;

            void UpdateSceneGraph(Entity entity);
            void UpdateEntityInSceneGraph(Entity entity, int level);
    };
}