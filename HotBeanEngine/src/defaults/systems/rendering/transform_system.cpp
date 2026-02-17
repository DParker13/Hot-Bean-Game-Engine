/**
 * @file transform_system.cpp
 * @author Daniel Parker
 * @brief System for managing the 2D transformations of game entities.
 * @version 0.1
 * @date 2025-02-18
 *
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/defaults/systems/rendering/transform_system.hpp>

namespace HBE::Default::Systems {
    void TransformSystem::OnEntityAdded(EntityID entity) {
        g_app.GetTransformManager().GetSceneGraph().AddEntity(entity, g_ecs.GetComponent<Transform2D>(entity).m_parent);
    }

    void TransformSystem::OnEntityRemoved(EntityID entity) {
        g_app.GetTransformManager().GetSceneGraph().RemoveEntity(entity);
    }
} // namespace HBE::Default::Systems