#pragma once

#include <HotBeanEngine/application/application.hpp>

namespace HBE::Application {

    /**
     * @brief Template-based archetype for creating entities with predefined component sets
     */
    template<typename... Cs>
    struct Archetype : public HBE::Core::IArchetype {
        // std::vector<std::string> GetComponentNames() {
        //     std::vector<std::string> component_names;
        //     ((AddToVector(component_names, static_cast<Component*>(new Cs))), ...);

        //     return component_names;
        // }

        // void AddToVector(std::vector<std::string>& archetype_vector, Component* archetype) {
        //     archetype_vector.push_back(archetype->GetName());
        //     delete archetype;
        // }

        static Entity Create(Cs&&... comps) {
            try {
                Entity entity = g_ecs.CreateEntity();
                (g_ecs.AddComponent<Cs>(entity, std::forward<Cs>(comps)), ...);

                return entity;
            }
            catch(const std::exception& e) {
                LOG(LoggingType::ERROR, e.what());
                throw;
            }
        }

        static Entity Create() {
            try {
                Entity entity = g_ecs.CreateEntity();
                (g_ecs.AddComponent<Cs>(entity), ...);

                return entity;
            } catch(const std::exception& e) {
                LOG(LoggingType::ERROR, e.what());
                throw;
            }
        }

        template<typename T>
        static T& Get(Entity entity) {
            try {
                return g_ecs.GetComponent<T>(entity);
            }
            catch (const std::runtime_error& e) {
                LOG(LoggingType::ERROR, e.what());
                throw;
            }
        }
    };
}