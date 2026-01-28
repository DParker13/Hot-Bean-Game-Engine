/**
 * @file example_game.hpp
 * @author Daniel Parker (DParker13)
 * @brief Example game implementation extending the Hot Bean Engine.
 * @version 0.1
 * @date 2025-06-12
 *
 * @copyright Copyright (c) 2025
 */
#pragma once

#include "../scenes/example_scene.hpp"

namespace Game {
    /**
     * @class ExampleGame
     * @brief Example game implementation demonstrating engine usage.
     * 
     * Extends the Application class with example game logic, scene management,
     * and custom systems. Serves as a template for creating new games with the engine.
     */
    class ExampleGame : public HBE::Application::Application {
    public:
        ExampleGame(const std::string &config_path,
                    std::shared_ptr<HBE::Application::IComponentFactory> component_factory,
                    std::unique_ptr<HBE::Application::GUI::IEditorGUI> editor_gui);
        ~ExampleGame() = default;

    protected:
        void OnStart() override;
    };
} // namespace Game