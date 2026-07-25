#include "build_manager.hpp"

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/serializers/binary/binary_scene_serializer.hpp>

namespace HBE::Editor::Managers {
    void BuildManager::BuildProject() {
        // Implement the build logic here
        // This could involve compiling code, packaging assets, etc.
        // For now, we'll just print a message to indicate that the build process has started.
        LOG(Core::LoggingType::INFO, "Starting build process for project: " + m_project_manager->m_project.m_name);

        // Example of accessing project files
        auto project_files = m_project_manager->GetProjectFiles();

        // TODO: Need to create a build script with parameter that takes all headers and source files and compiles them
        // into a single executable.
        for (const auto &file : project_files) {
            LOG(Core::LoggingType::INFO, "Processing file: " + file.string());
            // Add build logic for each file here
        }

        LOG(Core::LoggingType::INFO, "Build process completed.");
    }

    void BuildManager::GenerateSceneBinary() {
        LOG(Core::LoggingType::INFO, "Generating binary scenes...");

        auto &scene_manager = g_app.GetSceneManager();
        auto binary_serializer = g_app.GetSerializationManager().GetSerializer("BinarySceneSerializer");

        // Save which scene was loaded so we can restore it afterwards.
        auto previous_scene = scene_manager.GetCurrentScene();

        // Ensure the binary output directory exists.
        std::filesystem::path scene_path = m_project_manager->m_project.m_directory / "bin" / "assets" / "scenes";
        if (!std::filesystem::exists(scene_path))
            std::filesystem::create_directories(scene_path);

        int i = 0;
        for (auto &[name, scene] : scene_manager.m_scenes) {
            if (!std::filesystem::exists(scene->m_scene_path)) {
                LOG(Core::LoggingType::WARNING, "Scene file not found, skipping: " + scene->m_scene_path.string());
                continue;
            }

            // Load scene into ECS via the registered YAML serializer.
            scene_manager.LoadScene(scene, false);

            std::string file_name = std::to_string(i) + ".dat";
            binary_serializer->Serialize(scene_path / file_name);

            scene_manager.UnloadScene(false);

            i++;

            LOG(Core::LoggingType::INFO, "Generated: " + (scene_path / file_name).string());
        }

        // Restore the previously loaded scene.
        if (previous_scene) {
            scene_manager.LoadScene(previous_scene, false);
        }

        LOG(Core::LoggingType::INFO, "Binary scene generation complete.");
    }
} // namespace HBE::Editor::Managers