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

#include <HotBeanEngine/application/managers/component_listener.hpp>
#include <HotBeanEngine/defaults/components/miscellaneous/transform_2d.hpp>
#include <HotBeanEngine/defaults/utilities/scene_graph.hpp>

namespace HBE::Application::Managers {
    using HBE::Default::Utilities::SceneGraph;

    class TransformManager : public ComponentListener {
    private:
        SceneGraph m_scene_graph;

    public:
        TransformManager();
        ~TransformManager() = default;

        /**
         * @brief Called when a Transform2D component is added to an entity.
         * @param entity The entity that gained a Transform2D component.
         */
        void OnComponentAdded(HBE::Core::IComponent *component, HBE::Core::EntityID entity) override;

        /**
         * @brief Called when a Transform2D component is removed from an entity.
         * Cleans up the entity from the scene graph.
         * @param entity The entity that lost a Transform2D component.
         */
        void OnComponentRemoved(HBE::Core::EntityID entity) override;

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