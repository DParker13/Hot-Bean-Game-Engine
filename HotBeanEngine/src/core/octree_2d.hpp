#pragma once

#include "octree_2d_node.hpp"

namespace HBE::Core {
    template<typename T>
    struct Octree2D {
        // TODO: Create vector? with multiple octrees if items move outside of the root bounds

        Octree2DNode<T>* m_root = nullptr;
        int m_max_depth;

        Octree2D(glm::ivec3 bounds, int depth = 5) : m_root(new Octree2DNode<T>(bounds)), m_max_depth(depth) {};
        ~Octree2D() {
            delete m_root;
        }

        void Insert(T* item, const glm::vec2 position) {
            m_root->Insert(item, position, m_max_depth);
        }

        void Remove(T* item) {
            m_root->Remove(item);
        }

        void Remove(T* item, glm::vec2 position) {
            m_root->Remove(item, position);
        }

        std::vector<glm::ivec3> GetAllBounds() {
            std::vector<glm::ivec3> bounds;
            m_root->GetAllBounds(bounds);

            return bounds;
        }
    };
}