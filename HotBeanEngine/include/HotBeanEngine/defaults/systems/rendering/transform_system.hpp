#pragma once

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/defaults/components/default_components.hpp>

using namespace HBE::Default::Components;
using namespace HBE::Application;
using namespace HBE::Core;

namespace HBE::Default::Systems {
    class TransformSystem : public System {
        private:
            std::unordered_map<Entity, Uint32> m_entity_graph_level;
            std::map<Uint32, std::set<Entity>> m_scene_graph;
            
        public:
            DEFINE_SIGNATURE(TransformSystem, Transform2D);
            TransformSystem() : System("Transform System") {}

            void OnEntityAdded(Entity entity) override;
            void OnEntityRemoved(Entity entity) override;
            void OnUpdate() override;
        
        private:
            void UpdateSceneGraph(Entity entity);
            void UpdateEntityInSceneGraph(Entity entity, int level);
    };
}