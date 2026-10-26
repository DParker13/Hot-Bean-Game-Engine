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
#include <HotBeanEngine/core/iserializable.hpp>
#include <filesystem>
#include <iostream>
#include <string>

namespace HBE::Core {
    class Project : public ISerializable {
    public:
        std::string m_name = "New Project";
        float m_version = VERSION;
        std::string m_file_name = "new_project.yaml";
        std::filesystem::path m_directory = std::filesystem::current_path();
        std::vector<std::filesystem::path> m_scenes;

        void Serialize(ISerializationWriter &out) const override {
            out.BeginSection("Project");
            out.Write("name", m_name);
            out.Write("version", m_version);
            out.Write("directory", m_directory);
            out.EndSection();

            if (!m_scenes.empty()) {
                out.Write("Scenes", m_scenes);
            }
        }

        void Deserialize(ISerializationReader &in) override {
            in.BeginSection("Project");
            in.Read("name", m_name);
            in.Read("version", m_version);
            in.Read("directory", m_directory);
            in.EndSection();

            m_scenes.clear();
            in.Read("Scenes", m_scenes);
        }
    };
} // namespace HBE::Core