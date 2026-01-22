#pragma once

#include <HotBeanEngine/defaults/components/miscellaneous/transform_2d.hpp>

namespace HBE::Default::Helpers {
    using namespace HBE::Default::Components;
    
    /**
     * @brief Helper functions for transform operations
     * Provides utility functions for manipulating and converting transforms.
     */
    namespace TransformHelper {
        /**
         * @brief Propagate world-space transforms from parent to child
         * @param transform Transform to update
         * @param parent_transform Parent transform (nullptr if root)
         */
        inline void PropagateTransforms(Transform2D& transform, const Transform2D* parent_transform) {
            // Convert local position to world position based on parent
            if (transform.m_parent != -1 && parent_transform != nullptr) {
                transform.m_world_position = parent_transform->m_world_position + transform.m_local_position;
                transform.m_world_rotation = parent_transform->m_world_rotation + transform.m_local_rotation;
            }
            else {
                transform.m_world_position = transform.m_local_position;
                transform.m_world_rotation = transform.m_local_rotation;
            }
        }
    }
}