#pragma once

#include "app.hpp"

using namespace Core::Application;

namespace Core {
    namespace ECS {
        template <typename... Components>
        class GameObject {
            public:
                GameObject(App& app)
                    : GameObject(app, std::make_index_sequence<sizeof...(Components)>{}) {}
        
                template <std::size_t... Cs>
                GameObject(App& app, std::index_sequence<Cs...>)
                    : _app(app) {
                    _entity = _app.GetECSManager()->CreateEntity();
                    (_app.GetECSManager()->AddComponent<Components>(_entity, Components()), ...);
                }
        
                ~GameObject() {
                    _app.GetECSManager()->DestroyEntity(_entity);
                }
        
                template <typename Component>
                Component& GetComponent() {
                    return _app.GetECSManager()->GetComponent<Component>(_entity);
                }
        
                template <typename Component>
                void AddComponent() {
                    _app.GetECSManager()->AddComponent<Component>(_entity, Component());
                }

                Entity GetEntity() {
                    return _entity;
                };
        
                virtual void OnInit(Entity entity) {
                    assert(entity >= 0 && entity < MAX_ENTITIES && "Entity out of range.");
                };
                virtual void OnPreEvent(Entity entity) {
                    assert(entity >= 0 && entity < MAX_ENTITIES && "Entity out of range.");
                };
                virtual void OnEvent(SDL_Event& event, Entity entity) {
                    assert(entity >= 0 && entity < MAX_ENTITIES && "Entity out of range.");
                };
                virtual void OnUpdate(Entity entity) {
                    assert(entity >= 0 && entity < MAX_ENTITIES && "Entity out of range.");
                };
                virtual void OnRender(Entity entity) {
                    assert(entity >= 0 && entity < MAX_ENTITIES && "Entity out of range.");
                };
                virtual void OnPostRender(Entity entity) {
                    assert(entity >= 0 && entity < MAX_ENTITIES && "Entity out of range.");
                };
        
                virtual std::string ToString() const {
                    return "GameObject";
                };
            
            protected:
                Entity _entity = -1;
                App& _app;
                
        };
    }
}