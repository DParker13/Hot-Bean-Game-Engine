/**
 * @file scene.h
 * @author Daniel Parker (DParker13)
 * @brief Used to setup and control switching between other initialized scenes.
 * @version 0.1
 * @date 2025-03-24
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include <sstream>
#include <filesystem>

#include "app.hpp"
#include "object.hpp"
 
namespace Core {
    namespace ECS {
        struct Scene : public Object {
            std::string _name;
            std::string _scene_path;
            
            Scene(std::string name, std::string scene_path)
                : _name(name), _scene_path(scene_path) {}
            ~Scene() = default;

            virtual void SetupScene() = 0;
            virtual void UnloadScene() = 0;
    
            std::string ToString() const override {
                std::stringstream str;
                str << "    Component: Scene \n";
                
                return str.str();
            }
        };
    }
}