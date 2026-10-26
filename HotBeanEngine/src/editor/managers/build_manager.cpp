#include "build_manager.hpp"

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/serializers/binary/binary_entity_serializer.hpp>
#include <HotBeanEngine/serializers/binary/binary_serializer.hpp>

#include <cstdio>
#include <cstdlib>
#include <string>

#ifdef _WIN32
    #include <windows.h>
#endif

namespace HBE::Editor::Managers {
    namespace {
        std::string EscapeForDoubleQuotedShellArg(std::string value) {
            std::string escaped;
            escaped.reserve(value.size());

            for (const char ch : value) {
                if (ch == '\\' || ch == '"' || ch == '$' || ch == '`') {
                    escaped.push_back('\\');
                }
                escaped.push_back(ch);
            }

            return escaped;
        }

        int RunCommandWithLiveOutput(const std::filesystem::path &working_directory, const std::string &command,
                                     const std::string &phase) {
            const std::string shell_command = "cd \"" + working_directory.string() + "\" && " + command + " 2>&1";

            LOG(Core::LoggingType::INFO, phase + " started: " + command);

#ifdef _WIN32
            FILE *pipe = _popen(shell_command.c_str(), "r");
#else
            FILE *pipe = popen(shell_command.c_str(), "r");
#endif
            if (!pipe) {
                LOG(Core::LoggingType::ERROR, phase + " failed to start.");
                return -1;
            }

            char buffer[512];
            while (std::fgets(buffer, sizeof(buffer), pipe)) {
                std::string line(buffer);
                if (!line.empty() && line.back() == '\n') {
                    line.pop_back();
                }
                if (!line.empty() && line.back() == '\r') {
                    line.pop_back();
                }
                if (!line.empty()) {
                    LOG(Core::LoggingType::INFO, phase + ": " + line);
                }
            }

#ifdef _WIN32
            int exit_code = _pclose(pipe);
#else
            int exit_code = pclose(pipe);
#endif

            if (exit_code != 0) {
                LOG(Core::LoggingType::ERROR, phase + " finished with exit status: " + std::to_string(exit_code));
            }

            return exit_code;
        }
    } // namespace

    BuildManager::~BuildManager() {
        if (m_build_thread.joinable()) {
            m_build_thread.join();
        }
    }

    void BuildManager::BuildProject() {
        if (m_build_in_progress.exchange(true)) {
            LOG(Core::LoggingType::WARNING, "A build is already in progress.");
            return;
        }

        LOG(Core::LoggingType::INFO, "Starting build process for project: " + m_project_manager->m_project.m_name);

        // Bake scene data first so the release build has the serialized assets it needs.
        GenerateSceneBinaries();

        const std::filesystem::path root_dir = GetRootDir();
        const std::string executable_name =
            m_project_manager->m_project.m_name.empty() ? "HotBeanEngine" : m_project_manager->m_project.m_name;
        if (m_build_thread.joinable()) {
            m_build_thread.join();
        }

        m_build_thread = std::thread([this, root_dir, executable_name]() {
            const std::string configure_command =
                "cmake --preset release -DEXECUTABLE_NAME=\"" + EscapeForDoubleQuotedShellArg(executable_name) + "\"";
            const int configure_result = RunCommandWithLiveOutput(root_dir, configure_command, "Release configure");
            if (configure_result != 0) {
                m_build_in_progress = false;
                return;
            }

            const int build_result =
                RunCommandWithLiveOutput(root_dir, "cmake --build --preset release", "Release build");
            if (build_result != 0) {
                LOG(Core::LoggingType::ERROR, "Build process failed with exit status: " + std::to_string(build_result));
                m_build_in_progress = false;
                return;
            }

            LOG(Core::LoggingType::INFO, "Build process completed.");
            LOG(Core::LoggingType::INFO, "Copying executable to project bin directory.");

#ifdef _WIN32
            const std::filesystem::path build_output =
                root_dir / "build-release" / "HotBeanEngine" / "src" / (executable_name + ".exe");
#else
            const std::filesystem::path build_output =
                root_dir / "build-release" / "HotBeanEngine" / "src" / executable_name;
#endif

            if (std::filesystem::exists(build_output) && std::filesystem::is_regular_file(build_output)) {
                std::filesystem::copy_file(build_output, GetBuildDir() / build_output.filename(),
                                           std::filesystem::copy_options::overwrite_existing);
                LOG(Core::LoggingType::INFO,
                    "Executable copied to: " + (GetBuildDir() / build_output.filename()).string());
            }
            else {
                LOG(Core::LoggingType::WARNING, "Executable not found, skipping copy: " + build_output.string());
            }

            LOG(Core::LoggingType::INFO, "Executable copy step finished.");

            m_build_in_progress = false;
        });
    }

    void BuildManager::GenerateReleaseMetadataFile() {
        std::filesystem::path metadata_file_path = GetBuildDir() / "game.dat";
        std::ofstream metadata_file(metadata_file_path);

        if (!metadata_file.is_open()) {
            LOG(Core::LoggingType::ERROR, "Failed to create release metadata file: " + metadata_file_path.string());
            return;
        }

        metadata_file << "Project Name: " << m_project_manager->m_project.m_name << "\n";
        metadata_file << "Build Date: " << std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())
                      << "\n";
        metadata_file << "Executable Name: "
                      << (m_project_manager->m_project.m_name.empty() ? "HotBeanEngine"
                                                                      : m_project_manager->m_project.m_name)
                      << "\n";

        metadata_file.close();

        LOG(Core::LoggingType::INFO, "Release metadata file generated at: " + metadata_file_path.string());
    }

    void BuildManager::GenerateSceneBinaries() {
        LOG(Core::LoggingType::INFO, "Generating binary scenes...");

        auto &scene_manager = g_app.GetSceneManager();
        auto binary_serializer = std::make_shared<Serializers::BinarySerializer>();
        auto binary_entity_serializer = std::make_shared<Serializers::BinaryEntitySerializer>();

        // Save which scene was loaded so we can restore it afterwards.
        auto previous_scene = scene_manager.GetCurrentScene();

        // Ensure the binary output directory exists.
        std::filesystem::path scene_path = GetBuildDir() / "assets" / "scenes";

        int i = 0;
        for (auto &[name, scene] : scene_manager.m_scenes) {
            if (!std::filesystem::exists(scene->m_scene_path)) {
                LOG(Core::LoggingType::WARNING, "Scene file not found, skipping: " + scene->m_scene_path.string());
                continue;
            }

            // Load scene into ECS via the registered YAML serializer.
            scene_manager.LoadScene(scene);

            std::string file_name = std::to_string(i) + ".dat";
            binary_serializer->Serialize(scene_path / file_name, *scene);
            binary_entity_serializer->Serialize(scene_path / file_name, *scene, true);

            scene_manager.UnloadScene();

            i++;

            LOG(Core::LoggingType::INFO, "Generated: " + (scene_path / file_name).string());
        }

        // Restore the previously loaded scene.
        if (previous_scene) {
            scene_manager.LoadScene(previous_scene);
        }

        LOG(Core::LoggingType::INFO, "Binary scene generation complete.");
    }

    std::filesystem::path BuildManager::GetRootDir() const {
        return std::filesystem::current_path().parent_path().parent_path().parent_path();
    }

    std::filesystem::path BuildManager::GetBuildDir() const {
        std::filesystem::path bin_path = m_project_manager->m_project.m_directory / "bin";

        if (!std::filesystem::exists(bin_path))
            std::filesystem::create_directories(bin_path);

        return bin_path;
    }
} // namespace HBE::Editor::Managers