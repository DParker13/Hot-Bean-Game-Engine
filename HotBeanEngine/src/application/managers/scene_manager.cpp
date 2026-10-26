/**
 * @file scene_manager.cpp
 * @author Daniel Parker (DParker13)
 * @brief IScene manager for handling scene loading and unloading.
 * @version 0.1
 * @date 2025-02-23
 *
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/application/managers/scene_manager.hpp>

namespace HBE::Application::Managers {
    void SceneManager::LoadScene(std::shared_ptr<IScene> scene) {
        assert(scene && "IScene is null.");

        auto serializer = g_app.GetSerializationManager().GetSerializer("EntitySerializer");
        if (!serializer) {
            LOG(LoggingType::FATAL, "No serializer found for EntitySerializer");
            throw std::runtime_error("No serializer found for EntitySerializer");
        }

        if (!serializer->FileExists(scene->m_scene_path)) {
            LOG(LoggingType::FATAL, "Scene file does not exist: " + m_current_scene->m_scene_path.string());
            throw std::runtime_error("Scene file does not exist: " + m_current_scene->m_scene_path.string());
        }

        // Unload current scene if a new one is being loaded
        if (m_current_scene && m_current_scene != scene) {
            UnloadScene();
        }

        m_current_scene = scene;

        LOG(LoggingType::INFO, "Loading scene \"" + m_current_scene->m_name + "\" from file: ");
        LOG(LoggingType::INFO, "Scene path: " + m_current_scene->m_scene_path.string());

        // Deserialize scene from file
        serializer->Deserialize(m_current_scene->m_scene_path, *m_current_scene);

        g_ecs.IterateSystems(GameLoopState::OnStart);

        LOG(LoggingType::INFO, "Scene loaded.");

        m_current_scene->SetupScene();
    }

    void SceneManager::UnloadScene() {
        assert(m_current_scene && "Current scene is null.");

        LOG(LoggingType::INFO, "Unloading scene \"" + m_current_scene->m_name + "\" to file");
        LOG(LoggingType::INFO, "Scene path: " + m_current_scene->m_scene_path.string());

        // Call scene cleanup before destroying entities to allow systems to release resources
        m_current_scene->CleanupScene();

        g_ecs.DestroyAllEntities();
    }

    std::shared_ptr<IScene> SceneManager::GetCurrentScene() const { return m_current_scene; }

    bool SceneManager::IsSceneRegistered(std::shared_ptr<IScene> scene) {
        if (!scene) {
            LOG(LoggingType::ERROR, "Scene is null");
            return false;
        }

        return IsSceneRegistered(scene->m_name);
    }

    bool SceneManager::IsSceneRegistered(std::string_view name) { return m_scenes.count(std::string(name)) > 0; }

    void SceneManager::RegisterScene(std::shared_ptr<IScene> scene) {
        if (IsSceneRegistered(scene)) {
            LOG(LoggingType::WARNING, "Scene with that name already registered!");
            return;
        }

        m_scenes.emplace(scene->m_name, scene);
    }

    void SceneManager::UnregisterScene(std::shared_ptr<IScene> scene) {
        if (!IsSceneRegistered(scene)) {
            LOG(LoggingType::WARNING, "Scene with that name isn't registered!");
            return;
        }

        m_scenes.erase(scene->m_name);
    }

    void SceneManager::RemoveScene(std::shared_ptr<IScene> scene) {
        assert(scene && "Scene is null.");

        RemoveScene(scene->m_name);
    }

    void SceneManager::RemoveScene(std::string name) {
        assert(m_scenes.find(name) != m_scenes.end() && "Scene isn't registered.");

        if (m_current_scene->m_name == name) {
            UnloadScene();
        }

        m_scenes.erase(name);
    }

    void SceneManager::SwitchScene(std::shared_ptr<IScene> scene) {
        assert(scene && "Scene is null.");

        SwitchScene(scene->m_name);
    }

    void SceneManager::SwitchScene(std::string name) {
        assert(m_scenes.find(name) != m_scenes.end() && "Scene with that name does not exist.");
        LOG(LoggingType::INFO, "Switching to scene: " + name);

        // Loads the new scene
        LoadScene(m_scenes[name]);
    }

    void SceneManager::SerializeScene() {
        if (!m_current_scene) {
            LOG(LoggingType::WARNING, "No current scene to serialize.");
            return;
        }

        // Serialize scene first, then append entities to file
        if (auto scene_serializer = g_app.GetSerializationManager().GetSerializer("BasicSerializer")) {
            scene_serializer->Serialize(m_current_scene->m_scene_path, *m_current_scene);
            LOG(LoggingType::INFO, "Scene \"" + m_current_scene->m_name + "\" serialized.");
        }
        if (auto entity_serializer = g_app.GetSerializationManager().GetSerializer("EntitySerializer")) {
            entity_serializer->Serialize(m_current_scene->m_scene_path, *m_current_scene, true);
            LOG(LoggingType::INFO, "Scene \"" + m_current_scene->m_name + "\" entities serialized.");
        }
    }
} // namespace HBE::Application::Managers