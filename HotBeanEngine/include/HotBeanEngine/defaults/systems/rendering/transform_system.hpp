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

namespace HBE::Default::Systems {
    using namespace HBE::Core;
    using namespace HBE::Default::Components;
    
    /**
     * @brief Updates entity transforms and hierarchy
     * 
     * Computes world-space transforms from local transforms.
     * Handles parent-child transformation propagation.
     */
    class TransformSystem : public ISystem {
        private:
            std::unordered_map<EntityID, Uint32> m_entity_graph_level;
            std::map<Uint32, std::set<EntityID>> m_scene_graph;
            
        public:
            DEFINE_SIGNATURE(TransformSystem, "Transform System", Transform2D);
            TransformSystem() = default;
            ~TransformSystem() = default;

            void OnEntityAdded(EntityID entity) override;
            void OnEntityRemoved(EntityID entity) override;
            void OnUpdate() override;
        
        private:
            void UpdateSceneGraph(EntityID entity);
            void UpdateEntityInSceneGraph(EntityID entity, int level);
    };
}