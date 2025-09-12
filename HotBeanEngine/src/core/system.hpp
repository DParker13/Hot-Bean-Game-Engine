#pragma once

#include <set>

#include "app.hpp"
#include "entity.hpp"
#include "game_loop.hpp"

namespace HBE::Core {
    class System : public GameLoop {
        public:
            std::set<Entity> m_entities;
    
            System() = default;
            virtual ~System() = default;

            // System interface
            virtual void OnEntityRemoved(Entity entity) {};
            virtual void OnEntityAdded(Entity entity) {};
    
            // GameLoop interface
            virtual void SetSignature() = 0;
            virtual void OnStart() {};
            virtual void OnPreEvent() {};
            virtual void OnEvent(SDL_Event& event) {};
            virtual void OnWindowResize(SDL_Event& event) {};
            virtual void OnUpdate() {};
            virtual void OnRender() {};
            virtual void OnPostRender() {};
    };
}