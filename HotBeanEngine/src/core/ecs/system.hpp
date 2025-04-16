#pragma once

#include <SDL.h>
#include <set>

#include "app.hpp"
#include "entity.hpp"
#include "game_loop.hpp"
#include "object.hpp"

using namespace Core::Application;

namespace Core {
    namespace ECS {
        class System : public Object, public GameLoop {
            public:
                App& _app;
                std::set<Entity> _entities;
        
                System(App& app)
                    : _app(app) {};
        
                System() = default;
                virtual ~System() = default;
        
                // GameLoop interface
                virtual void OnInit() {};
                virtual void OnPreEvent() {};
                virtual void OnEvent(SDL_Event& event) {};
                virtual void OnUpdate() {};
                virtual void OnRender() {};
                virtual void OnPostRender() {};
        };
    }
}