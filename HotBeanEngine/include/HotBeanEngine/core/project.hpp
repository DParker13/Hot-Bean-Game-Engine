/**
 * @file project.hpp
 * @author Daniel Parker (DParker13)
 * @brief Managing project data and state.
 * @version 0.1
 * @date 2026-03-25
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <HotBeanEngine/core/config.hpp>
#include <filesystem>
#include <string>

namespace HBE::Core {
    class Project {
    public:
        std::string m_name = "New Project";
        float m_version = VERSION;
        std::string m_file = "new_project.yaml";
        std::filesystem::path m_directory = "";

        std::filesystem::path GetFullPath() const { return m_directory / m_file; }
    };
} // namespace HBE::Core