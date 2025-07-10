#pragma once

#include <typeindex>
#include "../application/app.hpp"

using namespace Core::Application;

namespace Core::ECS {

    template<typename... Cs>
    struct Archetype : public IArchetype {
        std::vector<std::string> GetComponentNames() {
            std::vector<std::string> component_names;
            ((AddToVector(component_names, static_cast<Component*>(new Cs))), ...);

            return component_names;
        }

        void AddToVector(std::vector<std::string>& archetype_vector, Component* archetype) {
            archetype_vector.push_back(archetype->GetName());
            delete archetype;
        }

        static Entity Create(Cs&&... comps) {
            App& app = App::GetInstance();

            try {
                Entity entity = app.CreateEntity();
                (app.AddComponent<Cs>(entity, std::forward<Cs>(comps)), ...);

                return entity;
            }
            catch(const std::exception& e) {
                throw;
            }
        }

        static Entity Create() {
            App& app = App::GetInstance();

            try {
                Entity entity = app.CreateEntity();
                (app.AddComponent<Cs>(entity), ...);

                return entity;
            } catch(const std::exception& e) {
                LOG(LoggingType::ERROR, e.what());
                throw;
            }
        }
    };
}