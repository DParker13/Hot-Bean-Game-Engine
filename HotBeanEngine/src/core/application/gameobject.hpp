#pragma once

#include "app.hpp"

using namespace Core::Application;

namespace Core::ECS {
    template <typename... Components>
    class GameObject {
        public:
            GameObject()
                : GameObject(std::make_index_sequence<sizeof...(Components)>{}) {}
    
            template <std::size_t... Cs>
            GameObject(std::index_sequence<Cs...>) {
                App& app = App::GetInstance();
                _entity = app.GetECSManager()->CreateEntity();
                (app.GetECSManager()->AddComponent<Components>(_entity, Components()), ...);
            }
    
            ~GameObject() {
                //App::GetInstance().GetECSManager()->DestroyEntity(_entity);
            }
    
            template <typename Component>
            Component& GetComponent() {
                return App::GetInstance().GetECSManager()->GetComponent<Component>(_entity);
            }
    
            template <typename Component>
            void AddComponent() {
                App::GetInstance().GetECSManager()->AddComponent<Component>(_entity, Component());
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
            
    };
}