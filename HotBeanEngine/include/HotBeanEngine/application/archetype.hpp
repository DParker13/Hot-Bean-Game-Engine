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
        //     ((AddToVector(component_names, static_cast<IComponent*>(new Cs))), ...);

        //     return component_names;
        // }

        // void AddToVector(std::vector<std::string>& archetype_vector, IComponent* archetype) {
        //     archetype_vector.push_back(archetype->GetName());
        //     delete archetype;
        // }

        static EntityID Create(Cs&&... comps) {
            try {
                EntityID entity = g_ecs.CreateEntity();
                (g_ecs.AddComponent<Cs>(entity, std::forward<Cs>(comps)), ...);

                return entity;
            }
            catch(const std::exception& e) {
                LOG(LoggingType::ERROR, e.what());
                throw;
            }
        }

        static EntityID Create() {
            try {
                EntityID entity = g_ecs.CreateEntity();
                (g_ecs.AddComponent<Cs>(entity), ...);

                return entity;
            } catch(const std::exception& e) {
                LOG(LoggingType::ERROR, e.what());
                throw;
            }
        }

        template<typename T>
        static T& Get(EntityID entity) {
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