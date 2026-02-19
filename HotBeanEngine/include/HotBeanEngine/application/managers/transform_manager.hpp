/**
 * @file transform_manager.hpp
 * @author Daniel Parker (DParker13)
 * @brief
 * @version 0.1
 * @date 2026-02-10
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <HotBeanEngine/defaults/utilities/scene_graph.hpp>

namespace HBE::Application::Managers {
    using HBE::Default::Utilities::SceneGraph;

    class TransformManager {
    private:
        SceneGraph m_scene_graph;

    public:
        TransformManager() : m_scene_graph(SceneGraph()) {};
        ~TransformManager() = default;

        void OnUpdate();
        void PropagateTransforms(Transform2D &transform, const Transform2D *parent_transform);

        /**
         * @brief Get reference to the scene graph
         * @return Scene graph reference
         */
        SceneGraph &GetSceneGraph() { return m_scene_graph; }
        const SceneGraph &GetSceneGraph() const { return m_scene_graph; }
    };
} // namespace HBE::Application::Managers