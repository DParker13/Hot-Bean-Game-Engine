#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <vector>
#include <memory>
#include <iostream>

#include "../managers/core_manager.hpp"

namespace Application {
    class Application {
        private:
            SDL_Window* _window;
            SDL_Renderer* _renderer;
            SDL_Surface* _surface;
            float _deltaTime;
            float _previousFrameTime;

            void InitSDL(std::string title, int width, int height);
            void CleanUpSDL();
            void UpdateDeltaTime();
        public:
            Core::CoreManager _coreManager;
            bool _quit;

            Application(std::string title, int width, int height);
            ~Application();

            void Run();
            virtual void InitLayer() = 0;
            virtual void PreEventLayer() = 0;
            virtual void EventLayer(SDL_Event event) = 0;
            virtual void UpdateLayer(float deltaTime) = 0;
            virtual void RenderLayer(SDL_Renderer* renderer, SDL_Window* window, SDL_Surface* surface) = 0;
            virtual void PostRenderLayer() = 0;
    };
}