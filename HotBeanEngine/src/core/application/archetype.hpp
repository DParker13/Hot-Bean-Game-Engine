#pragma once

#include <typeindex>
#include "app.hpp"

using namespace Core::Application;

namespace Core::ECS {
    template<typename... Components>
    struct Archetype {
        static constexpr std::array<std::type_index, sizeof...(Components)> GetTypes() {
            return { typeid(Components)... };
        }

        static Entity Create(Components&&... comps) {
            App& app = App::GetInstance();

            try {
                Entity entity = app.CreateEntity();
                (app.AddComponent<Components>(entity, std::forward<Components>(comps)), ...);

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
                (app.AddComponent<Components>(entity), ...);

                return entity;
            } catch(const std::exception& e) {
                LOG(LoggingType::ERROR, e.what());
                throw;
            }
        }
    };
}