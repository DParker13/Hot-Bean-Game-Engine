/**
 * @file dirty_flag.hpp
 * @author Daniel Parker (DParker13)
 * @brief Base class for components to track when their data has changed and needs to be reprocessed.
 * @version 0.1
 * @date 2025-11-02
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

namespace HBE::Core {
    /// @brief Base class for components to track when their data has changed and needs to be reprocessed.
    class DirtyFlag {
    private:
        bool m_dirty = true; // Initialize as dirty so new components get processed

    public:
        virtual void MarkDirty() { m_dirty = true; }

        virtual void MarkClean() { m_dirty = false; }

        virtual bool IsDirty() const { return m_dirty; }
    };
} // namespace HBE::Core