/**
 * @file scene_manager.hpp
 * @author Daniel Parker (DParker13)
 * @brief Manages game scenes and scene transitions.
 * @version 0.1
 * @date 2025-10-11
 *
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <memory>

#include <HotBeanEngine/application/managers/ecs_manager.hpp>

namespace HBE::Application::Managers {
    using namespace HBE::Core;

    /**
     * @brief Manages game scenes and scene transitions.
     * Handles scene loading, unloading, and switching.
     */
    class SceneManager {
    private:
        std::shared_ptr<ECSManager> m_ecs_manager;
        std::shared_ptr<LoggingManager> m_logging_manager;

        /// @brief Current scene
        std::shared_ptr<Scene> m_current_scene;

    public:
        /// @brief Map of names to scenes
        std::unordered_map<std::string, std::shared_ptr<Scene>> m_scenes;

        SceneManager(std::shared_ptr<ECSManager> ecs_manager, std::shared_ptr<LoggingManager> logging_manager);
        ~SceneManager() = default;

        void LoadScene(std::shared_ptr<Scene> scene);
        void LoadScene(std::shared_ptr<Scene> scene, bool save_to_file);
        void UnloadScene(bool save_to_file);
        std::shared_ptr<Scene> GetCurrentScene() const;

        void RegisterScene(std::shared_ptr<Scene> scene);
        void RemoveScene(std::string name, bool save_to_file);
        void RemoveScene(std::shared_ptr<Scene> scene, bool save_to_file);
        void SwitchScene(std::shared_ptr<Scene> scene);
        void SwitchScene(std::string name);
    };
} // namespace HBE::Application::Managers