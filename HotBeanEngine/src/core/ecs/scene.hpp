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

using namespace Core::Application;
 
namespace Core {
    namespace ECS {
        struct Scene : public Object {
            std::string _name;
            std::filesystem::path _scene_path;
            
            Scene(std::string name) : _name(name) {}
            ~Scene() = default;

            virtual void RegisterComponents(App& app) = 0;
            virtual void SetupScene(App& app) = 0;
            virtual void UnloadScene(App& app) = 0;
    
            std::string ToString() const override {
                std::stringstream str;
                str << "    Component: Scene \n";
                
                return str.str();
            }
        };
    }
}