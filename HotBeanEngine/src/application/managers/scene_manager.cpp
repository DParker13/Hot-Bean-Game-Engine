/**
 * @file scene_manager.cpp
 * @author Daniel Parker (DParker13)
 * @brief IScene manager for handling scene loading and unloading.
 * @version 0.1
 * @date 2025-02-23
 *
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/application/managers/scene_manager.hpp>

namespace HBE::Application::Managers {

    SceneManager::SceneManager(std::shared_ptr<ECSManager> ecs_manager, std::shared_ptr<LoggingManager> logging_manager)
        : m_ecs_manager(ecs_manager), m_logging_manager(logging_manager) {}

    void SceneManager::LoadScene(std::shared_ptr<IScene> scene) { LoadScene(scene, false); }

    void SceneManager::LoadScene(std::shared_ptr<IScene> scene, bool save_to_file) {
        assert(scene && "IScene is null.");

        try {
            // Unload current scene if a new one is being loaded
            if (m_current_scene && m_current_scene != scene) {
                UnloadScene(save_to_file);
            }

            m_current_scene = scene;

            LOG_CORE(LoggingType::INFO, "Loading scene \"" + m_current_scene->m_name + "\" from file: ");
            LOG_CORE(LoggingType::INFO, "Scene path: " + m_current_scene->m_scene_path.string());

            // Attempt to load scene from file
            if (m_current_scene->m_serializer &&
                !m_current_scene->m_serializer->FileExists(m_current_scene->m_scene_path)) {
                LOG_CORE(LoggingType::FATAL, "Scene file does not exist: " + m_current_scene->m_scene_path.string());
                throw std::runtime_error("Scene file does not exist: " + m_current_scene->m_scene_path.string());
            }

            m_current_scene->SetupSystems();

            if (m_current_scene->m_serializer)
                m_current_scene->m_serializer->Deserialize(m_current_scene->m_scene_path);

            m_ecs_manager->IterateSystems(GameLoopState::OnStart);

            LOG_CORE(LoggingType::INFO, "Scene loaded.");
        } catch (const YAML::Exception &e) {
            LOG_CORE(LoggingType::ERROR, "Error parsing YAML file: " + (std::string)e.what());
        }

        m_current_scene->SetupScene();
    }

    void SceneManager::UnloadScene(bool save_to_file) {
        assert(m_current_scene && "Current scene is null.");

        try {
            LOG_CORE(LoggingType::INFO, "Unloading scene \"" + m_current_scene->m_name + "\" to file");
            LOG_CORE(LoggingType::INFO, "Scene path: " + m_current_scene->m_scene_path.string());

            // Attempt to serialize scene to file
            if (save_to_file && m_current_scene->m_serializer) {
                m_current_scene->m_serializer->Serialize(m_current_scene->m_scene_path);
                LOG_CORE(LoggingType::INFO, "Scene \"" + m_current_scene->m_name + "\" serialized.");
            }

            // Call scene cleanup before destroying entities to allow systems to release resources
            m_current_scene->CleanupScene();

            m_ecs_manager->DestroyAllEntities();
        } catch (const YAML::Exception &e) {
            LOG_CORE(LoggingType::ERROR, "Error serializing to YAML file: " + (std::string)e.what());
        }
    }

    std::shared_ptr<IScene> SceneManager::GetCurrentScene() const { return m_current_scene; }

    bool SceneManager::IsSceneRegistered(std::shared_ptr<IScene> scene) {
        if (!scene) {
            LOG_CORE(LoggingType::ERROR, "Scene is null");
            return false;
        }

        return IsSceneRegistered(scene->m_name);
    }

    bool SceneManager::IsSceneRegistered(std::string_view name) { return m_scenes.count(std::string(name)) > 0; }

    void SceneManager::RegisterScene(std::shared_ptr<IScene> scene) {
        if (IsSceneRegistered(scene)) {
            LOG_CORE(LoggingType::WARNING, "Scene with that name already registered!");
            return;
        }

        m_scenes.emplace(scene->m_name, scene);
    }

    void SceneManager::UnregisterScene(std::shared_ptr<IScene> scene) {
        if (!IsSceneRegistered(scene)) {
            LOG_CORE(LoggingType::WARNING, "Scene with that name isn't registered!");
            return;
        }

        m_scenes.erase(scene->m_name);
    }

    void SceneManager::RemoveScene(std::shared_ptr<IScene> scene, bool save_to_file) {
        assert(scene && "Scene is null.");

        RemoveScene(scene->m_name, save_to_file);
    }

    void SceneManager::RemoveScene(std::string name, bool save_to_file) {
        assert(m_scenes.find(name) != m_scenes.end() && "Scene isn't registered.");

        if (m_current_scene->m_name == name) {
            UnloadScene(save_to_file);
        }

        m_scenes.erase(name);
    }

    void SceneManager::SwitchScene(std::shared_ptr<IScene> scene) {
        assert(scene && "Scene is null.");

        SwitchScene(scene->m_name);
    }

    void SceneManager::SwitchScene(std::string name) {
        assert(m_scenes.find(name) != m_scenes.end() && "Scene with that name does not exist.");
        LOG_CORE(LoggingType::INFO, "Switching to scene: " + name);

        // Loads the new scene
        LoadScene(m_scenes[name]);
    }
} // namespace HBE::Application::Managers