/**
 * @file transform_system.hpp
 * @author Daniel Parker (DParker13)
 * @brief System for 2D transform management.
 * @version 0.1
 * @date 2025-03-02
 * 
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/defaults/components/default_components.hpp>

using namespace HBE::Default::Components;
using namespace HBE::Application;
using namespace HBE::Core;

namespace HBE::Default::Systems {
    /**
     * @brief Updates entity transforms and hierarchy
     * 
     * Computes world-space transforms from local transforms.
     * Handles parent-child transformation propagation.
     */
    class TransformSystem : public System {
        private:
            std::unordered_map<Entity, Uint32> m_entity_graph_level;
            std::map<Uint32, std::set<Entity>> m_scene_graph;
            
        public:
            DEFINE_SIGNATURE(TransformSystem, "Transform System", Transform2D);
            TransformSystem() = default;
            ~TransformSystem() = default;

            void OnEntityAdded(Entity entity) override;
            void OnEntityRemoved(Entity entity) override;
            void OnUpdate() override;
        
        private:
            void UpdateSceneGraph(Entity entity);
            void UpdateEntityInSceneGraph(Entity entity, int level);
    };
}