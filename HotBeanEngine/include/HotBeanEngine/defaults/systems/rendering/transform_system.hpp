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
#include <HotBeanEngine/defaults/helpers/transform_helper.hpp>
#include <HotBeanEngine/defaults/utilities/scene_graph.hpp>

namespace HBE::Default::Systems {
    using namespace HBE::Core;
    using namespace HBE::Default::Components;
    using namespace HBE::Default::Helpers;
    using namespace HBE::Default::Utilities;

    /**
     * @brief Updates entity transforms and hierarchy
     *
     * Computes world-space transforms from local transforms.
     * Handles parent-child transformation propagation.
     */
    class TransformSystem : public ISystem {
    private:
        SceneGraph m_scene_graph;

    public:
        DEFINE_SIGNATURE(TransformSystem, "Transform System", Transform2D);
        TransformSystem();
        ~TransformSystem() = default;

        void OnEntityAdded(EntityID entity) override;
        void OnEntityRemoved(EntityID entity) override;
        void OnUpdate() override;

        /**
         * @brief Get reference to the scene graph
         * @return Scene graph reference
         */
        SceneGraph &GetSceneGraph() { return m_scene_graph; }
        const SceneGraph &GetSceneGraph() const { return m_scene_graph; }
    };
} // namespace HBE::Default::Systems