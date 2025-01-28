#include "application.hpp"

// Include GameObjects
#include "../gameobjects/text.hpp"
#include "../gameobjects/player.hpp"
#include "../gameobjects/tile.hpp"

// Include Systems
#include "../systems/physics_system.hpp"
#include "../systems/render_system.hpp"
#include "../systems/input_system.hpp"
#include "../systems/player_controller_system.hpp"
#include "../systems/ui_system.hpp"
#include "../systems/tilemap_system.hpp"
#include "../systems/audio_system.hpp"

namespace Application {
    // Interface for all Application layers ordered in calling order
    class Game : public Application {
        public:
            Game(std::string title, int width, int height)
                : Application(title, width, height) {};
            ~Game();

            void InitSystems() override;
            void OnInit() override;
            void OnPreEvent() override {};
            void OnEvent(SDL_Event& event) override;
            void OnUpdate(float deltaTime) override;
            void OnRender(SDL_Renderer* renderer, SDL_Window* window, SDL_Surface* surface) override;
            void OnPostRender() override {};
    };
}