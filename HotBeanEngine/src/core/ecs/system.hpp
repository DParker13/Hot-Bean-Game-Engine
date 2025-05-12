#pragma once

#include <set>

#include "app.hpp"
#include "entity.hpp"
#include "game_loop.hpp"

using namespace Core::Application;

namespace Core {
    namespace ECS {
        class System : public GameLoop {
            public:
                std::set<Entity> m_entities;
        
                System() = default;
                virtual ~System() = default;
        
                // GameLoop interface
                virtual void OnStart() {};
                virtual void OnPreEvent() {};
                virtual void OnEvent(SDL_Event& event) {};
                virtual void OnUpdate() {};
                virtual void OnRender() {};
                virtual void OnPostRender() {};
        };
    }
}