/**
 * @file ifield_changed.hpp
 * @author Daniel Parker (DParker13)
 * @brief Interface for components that track field changes.
 * @version 0.1
 * @date 2025-11-02
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

namespace HBE::Core {
    /// @brief Interface for objects used to track member changes.
    class IMemberChanged {
    private:
        bool m_dirty = true; // Initialize as dirty so new components get processed

    public:
        virtual void MarkDirty() { m_dirty = true; }

        virtual void MarkClean() { m_dirty = false; }

        virtual bool IsDirty() const { return m_dirty; }
    };
} // namespace HBE::Core