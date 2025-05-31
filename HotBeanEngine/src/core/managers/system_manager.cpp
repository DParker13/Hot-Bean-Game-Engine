/**
 * @file system_manager.cpp
 * @author Daniel Parker (DParker13)
 * @brief Manages component-system relationship.
 * 
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "system_manager.hpp"
#include "../managers/logging_manager.hpp"

namespace Core::Managers {

    SystemManager::SystemManager(std::shared_ptr<LoggingManager> logging_manager)
        : m_logging_manager(logging_manager) {}

    SystemManager::~SystemManager() {
        for (auto& [name, system] : m_systems) {
            delete system;
            system = nullptr;
        }
    }

    /**
     * Erases a destroyed entity from all system lists.
     *
     * @param entity The ID of the entity that was destroyed.
     */
    void SystemManager::EntityDestroyed(Entity entity)
    {
        int erased_entities = 0;

        m_logging_manager->Log(LoggingType::DEBUG, "Destroying Entity \"" + std::to_string(entity) + "\"");

        // Erase a destroyed entity from all system lists
        // m_entities is a set so no check needed
        for (auto& [type_name, system] : m_systems) {
            erased_entities += system->m_entities.erase(entity);
        }

        m_logging_manager->Log(LoggingType::DEBUG, "\tErased Entity \"" + std::to_string(entity) + "\" from " + std::to_string(erased_entities) + " Systems");
    }

    /**
     * Notifies each system that an entity's signature has changed.
     *
     * @param entity The ID of the entity whose signature has changed.
     * @param entity_signature The new signature of the entity.
     *
     * This function iterates over each system and checks if the entity's new signature matches the system's signature.
     * If it does, the entity is added to the system's set of entities. If it does not, the entity is removed from the system's set of entities.
     */
    void SystemManager::EntitySignatureChanged(Entity entity, Signature entity_signature)
    {
        int entity_added_to_systems = 0;
        int entity_removed_from_systems = 0;

        m_logging_manager->Log(LoggingType::DEBUG, "Entity \"" + std::to_string(entity) + "\" Signature changed to"
            " \"" + entity_signature.to_string() + "\" updating Systems");

        // Notify each system that an entity's signature changed
        for (auto& [type_name, system] : m_systems) {
            auto const& system_signature = m_signatures[type_name];

            // Entity signature matches system signature - insert into set
            if ((entity_signature & system_signature) == system_signature) {
                system->m_entities.insert(entity);
                system->OnEntityAdded(entity);
                entity_added_to_systems++;
            }
            // Entity signature does not match system signature - erase from set
            else if (system->m_entities.erase(entity) != 0) {
                system->OnEntityRemoved(entity);
                entity_removed_from_systems++;
            }
        }

        if (entity_added_to_systems > 0) {
            m_logging_manager->Log(LoggingType::DEBUG, "\tAdded Entity \"" + std::to_string(entity) + "\" to " + std::to_string(entity_added_to_systems) + " Systems");
        }

        if (entity_removed_from_systems > 0) {
            m_logging_manager->Log(LoggingType::DEBUG, "\tRemoved Entity \"" + std::to_string(entity) + "\" from " + std::to_string(entity_removed_from_systems) + " Systems");
        }
    }

    /**
     * @brief Iterates all systems and calls specific game loop method
     * 
     * @param state Current game loop state
     */
    void SystemManager::IterateSystems(GameLoopState state) {
        for (auto& [type_name, system] : m_systems) {
            switch(state) {
                case GameLoopState::OnInit:
                    system->OnStart();
                    break;
                case GameLoopState::OnPreEvent:
                    system->OnPreEvent();
                    break;
                case GameLoopState::OnUpdate:
                    system->OnUpdate();
                    break;
                case GameLoopState::OnRender:
                    system->OnRender();
                    break;
                case GameLoopState::OnPostRender:
                    system->OnPostRender();
                    break;
            }
        }
    }

    void SystemManager::IterateSystems(SDL_Event& event, GameLoopState state) {
        for (auto& [type_name, system] : m_systems) {
            switch(state) {
                case GameLoopState::OnEvent:
                    system->OnEvent(event);
                    break;
                case GameLoopState::OnWindowResize:
                    system->OnWindowResize(event);
                    break;
            }
        }
    }
}