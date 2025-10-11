#pragma once

#include <HotBeanEngine/core/octree_2d_node.hpp>

namespace HBE::Core {
    template<typename T>
    struct Octree2D {
        // TODO: Create vector? with multiple octrees if items move outside of the root bounds

        Octree2DNode<T>* m_root = nullptr;
        int m_max_depth;
        std::unordered_map<T, Octree2DNode<T>*> m_item_to_node;

        Octree2D(glm::ivec3 bounds, int depth = 5) : m_root(new Octree2DNode<T>(bounds)), m_max_depth(depth) {};
        ~Octree2D() {
            delete m_root;
        }

        void Insert(T* item, const glm::vec2 position) {
            m_root->Insert(item, position, m_max_depth, *m_item_to_node);
        }

        void Remove(T* item) {
            m_root->Remove(item);
            m_item_to_node.erase(*item);
        }

        void Remove(T* item, glm::vec2 position) {
            m_root->Remove(item, position);
        }

        Octree2DNode<T>* Find(T* item) {
            return m_item_to_node[m_item_to_node];
        }

        std::vector<glm::ivec3> GetAllBounds() {
            std::vector<glm::ivec3> bounds;
            m_root->GetAllBounds(bounds);

            return bounds;
        }
    };
}