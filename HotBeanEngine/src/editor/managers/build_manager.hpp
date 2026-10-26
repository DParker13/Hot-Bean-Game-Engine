#pragma once

#include "project_manager.hpp"

#include <atomic>
#include <thread>

namespace HBE::Editor::Managers {
    class BuildManager {
    private:
        std::shared_ptr<ProjectManager> m_project_manager;
        std::thread m_build_thread;
        std::atomic_bool m_build_in_progress = false;

    public:
        BuildManager(std::shared_ptr<Managers::ProjectManager> project_manager) : m_project_manager(project_manager) {};
        ~BuildManager();

        void BuildProject();

        /**
         * @brief Generate a scene_factory file that contains the necessary code to register and create scenes
         * dynamically based on their class names.
         */
        void GenerateSceneFactory();

        void GenerateReleaseMetadataFile();

    private:
        /**
         * @brief Compile all yaml scenes into binary files.
         */
        void GenerateSceneBinaries();
        std::filesystem::path GetRootDir() const;
        std::filesystem::path GetBuildDir() const;
    };
} // namespace HBE::Editor::Managers