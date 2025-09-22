#pragma once

#include "../../application/all_application.hpp"

using namespace HBE::Application;
using namespace HBE::Core;

namespace Systems {
    class TransformSystem : public System {
        private:
            std::unordered_map<Entity, Uint32> m_entity_graph_level;
            std::map<Uint32, std::set<Entity>> m_scene_graph;
            
        public:
            DEFINE_SIGNATURE(TransformSystem, Transform2D);
            TransformSystem();

            void OnEntityAdded(Entity entity) override;
            void OnEntityRemoved(Entity entity) override;
            void OnUpdate() override;
        
        private:
            void UpdateSceneGraph(Entity entity);
            void UpdateEntityInSceneGraph(Entity entity, int level);
    };
}