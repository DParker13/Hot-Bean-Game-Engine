/**
 * @file game.cpp
 * @author Daniel Parker (DParker13)
 * @brief Game logic implementation.
 * Handles game state updates, user input processing, and rendering ontop of the Application class.
 * @version 0.1
 * @date 2025-02-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "game.hpp"

namespace Core {
    namespace Application {
        Game::Game(std::string title, int width, int height)
            : App(title, width, height) {}
    
        Game::~Game() {
            App::~App();
        }
    
        /**
         * @brief Initializes all systems in the game. This function creates an 
         * instance of each system that is used in the game.
         * 
         * @note The System Manager is responsible for cleaning up these
         * systems when they're no longer needed.
         */
        void Game::InitSystems() {
            App& app = static_cast<App&>(*this);

            new PhysicsSystem(app);
            new RenderSystem(app);
            new InputSystem(app);
            new PlayerControllerSystem(app);
            new UISystem(app);
            new TileMapSystem(app);
            new AudioSystem(app);
        }
    
        /**
         * @brief Initializes gameobjects and sets up their starting state.
         */
        void Game::OnInit() {
            App::OnInit();

            std::shared_ptr<TestScene> testScene = std::make_shared<TestScene>(TestScene());
            //GetSceneManager()->RegisterScene(testScene);

            //GetSceneManager()->LoadScene(testScene);
        }
    
        /**
         * @brief Calls the OnEvent method of all systems and each system
         * will handle their SDL events.
         */
        void Game::OnEvent(SDL_Event& event) {
            App::OnEvent(event);
        }
    
        /**
         * @brief Calls the OnUpdate method of all systems and each system
         * will update their entities.
         */
        void Game::OnUpdate() {
            App::OnUpdate();
        }
    
        /**
         * @brief Calls the OnRender method of all systems and each system
         * will render their entities and resources to the screen.
         */
        void Game::OnRender() {
            App::OnRender();
        }
    
        /**
         * @brief Calls the OnPostRender method of all systems.
         */
        void Game::OnPostRender() {
            App::OnPostRender();
        }
    }
}