#pragma once

#include "project_manager.hpp"

namespace HBE::Editor::Managers {
    class BuildManager {
    private:
        std::shared_ptr<ProjectManager> m_project_manager;

    public:
        BuildManager(std::shared_ptr<Managers::ProjectManager> project_manager) : m_project_manager(project_manager) {};
        ~BuildManager() = default;

        void BuildProject();

        /**
         * @brief Compile all yaml scenes into a single binary file.
         */
        void GenerateSceneBinary();

        /**
         * @brief Generate a scene_factory file that contains the necessary code to register and create scenes
         * dynamically based on their class names.
         */
        void GenerateSceneFactory();
    };
} // namespace HBE::Editor::Managers