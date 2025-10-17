#pragma once

#include <set>

#include <HotBeanEngine/core/entity.hpp>
#include <HotBeanEngine/core/game_loop.hpp>

namespace HBE::Core {
    class System : public GameLoop {
        public:
            std::set<Entity> m_entities;
            std::string m_name = "Nameless System";
    
            System(std::string name) : m_name(name) {};
            System() : m_name("Nameless System") {};
            virtual ~System() = default;

            // System interface
            virtual void SetSignature() = 0;
            virtual void OnEntityRemoved(Entity entity) {};
            virtual void OnEntityAdded(Entity entity) {};
    
            // GameLoop interface
            virtual void OnStart() {};
            virtual void OnPreEvent() {};
            virtual void OnEvent(SDL_Event& event) {};
            virtual void OnWindowResize(SDL_Event& event) {};
            virtual void OnFixedUpdate() {};
            virtual void OnUpdate() {};
            virtual void OnRender() {};
            virtual void OnPostRender() {};
    };
}