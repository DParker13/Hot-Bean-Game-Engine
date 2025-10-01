/**
 * @file scene.hpp
 * @author Daniel Parker (DParker13)
 * @brief Used to setup and control switching between other initialized scenes.
 * @version 0.1
 * @date 2025-03-24
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once
 
namespace HBE::Core {
    struct Scene {
        std::string m_name;
        std::string m_scene_path;
        
        Scene(std::string name, std::string scene_path)
            : m_name(name), m_scene_path(scene_path) {}
        ~Scene() = default;

        virtual void SetupScene() = 0;
        /**
         * @brief Initializes the systems needed for this scene in the system manager.
         */
        virtual void SetupSystems() = 0;
    };
}