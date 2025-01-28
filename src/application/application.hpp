#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <vector>
#include <memory>
#include <iostream>

#include "../core/managers/core_manager.hpp"

namespace Application {
    class Application {
        public:
            Core::CoreManager _coreManager;
            bool _quit;

            Application(std::string title, int width, int height);
            ~Application();

            void Run();
            virtual void InitSystems() = 0;
            virtual void OnInit() = 0;
            virtual void OnPreEvent() = 0;
            virtual void OnEvent(SDL_Event& event) = 0;
            virtual void OnUpdate(float deltaTime) = 0;
            virtual void OnRender(SDL_Renderer* renderer, SDL_Window* window, SDL_Surface* surface) = 0;
            virtual void OnPostRender() = 0;

        private:
            SDL_Window* _window;
            SDL_Renderer* _renderer;
            SDL_Surface* _surface;
            float _deltaTime;
            float _previousFrameTime;

            void InitApplication(std::string title, int width, int height);
            void CleanUpSDL();
            void UpdateDeltaTime();
    };
}