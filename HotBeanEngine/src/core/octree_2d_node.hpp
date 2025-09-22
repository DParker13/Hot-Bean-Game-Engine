#pragma once

#include <queue>
#include "glm/glm.hpp"

namespace HBE::Core {

    template<typename T>
    struct Octree2DNode {
        glm::ivec3 m_bounds; // Top Left Bounding Box (x, y, size)
        std::array<Octree2DNode<T>*, 4> m_child_nodes; // Child nodes
        std::vector<const T*> m_items; // Items in this node
        
        Octree2DNode(glm::ivec3 bounds) : m_bounds(bounds) {
            m_child_nodes[0] = nullptr;
            m_child_nodes[1] = nullptr;
            m_child_nodes[2] = nullptr;
            m_child_nodes[3] = nullptr;
        }

        ~Octree2DNode() {
            for (int i = 0; i < 4; i++) {
                delete m_child_nodes[i];
                m_child_nodes[i] = nullptr;
            }
        }

        void Insert(T* item, const glm::vec2 position, const int depth, std::unordered_map<T, Octree2DNode<T>*> item_to_node) {
            if (depth > 0) {
                // If there are no child nodes, create them
                if (m_child_nodes[0] == nullptr) {
                    CreateChildNodes();
                }

                // Check if the position is within any of the child nodes
                for (int i = 0; i < 4; i++) {
                    if (m_child_nodes[i]->WithinBounds(position)) {
                        m_child_nodes[i]->Insert(item, position, depth - 1, item_to_node);
                        return;
                    }
                }
            }

            m_items.push_back(item);

            // Add to item map for easier retrieval later
            if (!item_to_node[*item]) {
                item_to_node[*item] = this;
            }
        }

        /**
         * @brief Traverses the octree to remove an item from any nodes that contain it.
         * Searches all nodes.
         * 
         * @param item Item to remove
         */
        void Remove(T* item) {
            if (!IsLeaf()) {
                for (auto& child : m_child_nodes) {
                    if (child != nullptr && !child.IsEmpty()) {
                        child->Remove(item);
                        
                        if (child->IsEmpty()) {
                            delete child;
                            m_child_nodes = nullptr;
                        }
                    }
                }
            }
            else if (m_items.size() > 0) {
                int index = m_items.find(item);

                // If the item is not found in this node, return
                if (index == -1) {
                    return;
                }

                m_items.erase(index);

                // If the node is now empty, delete all child nodes
                if (m_items.size() == 0) {
                    ClearChildren();
                }
            }
        }

        /**
         * @brief Traverses the octree to remove an item from any nodes that contain it.
         * Can be used to remove an item from a specific node.
         * 
         * @param item Item to remove
         * @param position Position to check
         */
        void Remove(T* item, const glm::vec2 position) {
            // Check if the position is within the node's bounds
            if (WithinBounds(position)) {
                // If there are child nodes, recursively remove the item
                if (!IsLeaf()) {
                    for (auto& child : m_child_nodes) {
                        if (child != nullptr && !child.IsEmpty()) {
                            child->Remove(item, position);
                            
                            if (child->IsEmpty()) {
                                delete child;
                                m_child_nodes = nullptr;
                            }
                        }
                    }
                }
                else if (m_items.size() > 0) {
                    int index = m_items.find(item);

                    if (index == -1) {
                        return;
                    }

                    m_items.erase(index);

                    // If the node is now empty, remove it
                    if (m_items.size() == 0) {
                        ClearChildren();
                    }
                }
            }
        }

        /**
         * @brief Get the Items object
         * @return std::vector<T*> containing the all node items
         */
        std::vector<T*> GetItems() {
            return m_items;
        }

        /**
         * @brief Checks if the node is empty
         * @return True if the node is empty
         */
        bool IsEmpty() const {
            return m_items.empty();
        }

        /**
         * @brief Checks if the node has no children
         * 
         * @return True if the node has no children
         */
        bool IsLeaf() const {
            return m_child_nodes[0] == nullptr &&
                   m_child_nodes[1] == nullptr &&
                   m_child_nodes[2] == nullptr &&
                   m_child_nodes[3] == nullptr;
        }

        /**
         * @brief Checks if a position is within the node's bounding box
         * 
         * @param position Position to check
         * @return True if the position is within the node's bounding box
         */
        bool WithinBounds(glm::vec2 position) const {
            return position.x > m_bounds.x &&
                   position.x <= m_bounds.x + m_bounds.z &&
                   position.y > m_bounds.y &&
                   position.y <= m_bounds.y + m_bounds.z;
        }

        /**
         * @brief Create 4 Child Octree2DNode objects
         */
        void CreateChildNodes() {
            int child_size = (int)(m_bounds.z * 0.5f);

            m_child_nodes[0] = new Octree2DNode(glm::ivec3(m_bounds.x, m_bounds.y, child_size));
            m_child_nodes[1] = new Octree2DNode(glm::ivec3(m_bounds.x + child_size, m_bounds.y, child_size));
            m_child_nodes[2] = new Octree2DNode(glm::ivec3(m_bounds.x, m_bounds.y + child_size, child_size));
            m_child_nodes[3] = new Octree2DNode(glm::ivec3(m_bounds.x + child_size, m_bounds.y + child_size, child_size));
        }

        void GetAllBounds(std::vector<glm::ivec3>& bounds) {
            bounds.push_back(m_bounds);

            if (!IsLeaf()) {
                for (auto& child : m_child_nodes) {
                    if (child != nullptr) {
                        child->GetAllBounds(bounds);
                    }
                }
            }
        }

        void ClearChildren() {
            for (int i = 0; i < 4; i++) {
                delete m_child_nodes[i];
                m_child_nodes[i] = nullptr;
            }
        }
    };
}