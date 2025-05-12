/**
 * @file system_manager.hpp
 * @author Daniel Parker (DParker13)
 * @brief Manages component-system relationship.
 * 
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include <unordered_map>
#include <cassert>
#include <sstream>

#include "../ecs/all_ecs.hpp"
#include "../managers/logging_manager.hpp"

using namespace Core::ECS;

namespace Core::Managers {
	class SystemManager {
		public:
			SystemManager(std::shared_ptr<LoggingManager> logging_manager);
			~SystemManager();

			/**
			 * Registers a system with the SystemManager.
			 *
			 * @tparam T The type of system to be registered.
			 *
			 * @return A shared pointer to the system.
			 *
			 * @throws assertion failure if the system type has already been registered.
			 */
			template<typename T>
			T& RegisterSystem(T* system)
			{
				std::string type_name = typeid(T).name();
				assert(m_systems.find(type_name) == m_systems.end() && "Registering system more than once.");

				m_logging_manager->Log(LoggingType::DEBUG, "Registering System \"" + type_name + "\"");

				// Create a pointer to the system and return it so it can be used externally
				m_systems.insert({type_name, system});

				return *system;
			}

			/**
			 * Sets the signature for a system that has already been registered.
			 *
			 * @tparam T The type of system to be registered.
			 *
			 * @param signature The signature for the system.
			 *
			 * @throws assertion failure if the system type has not been registered.
			 */
			template<typename T>
			void SetSignature(Signature signature) {
				std::string type_name = typeid(T).name();
				assert(m_systems.find(type_name) != m_systems.end() && "System used before registered.");

				m_logging_manager->Log(LoggingType::DEBUG, "System \"" + type_name + "\" Signature set to"
					" \"" + signature.to_string() + "\"");

				// Set the signature for this system
				m_signatures.insert({type_name, signature});
			}

			/**
			 * Retrieves the signature associated with a system of type T.
			 *
			 * @tparam T The type of system to retrieve the signature for.
			 *
			 * @return A reference to the signature associated with the system of type T.
			 *
			 * @throws assertion failure if the system type has not been registered.
			 */
			template<typename T>
			Signature& GetSignature() {
				std::string type_name = typeid(T).name();
				assert(m_systems.find(type_name) != m_systems.end() && "System used before registered.");

				// Set the signature for this system
				return m_signatures[type_name];
			}

			/**
			 * Retrieves a previously registered system by its type.
			 *
			 * @tparam T The type of system to be retrieved.
			 *
			 * @return A shared pointer to the system.
			 *
			 * @throws assertion failure if the system type has not been registered.
			 */
			template <typename T>
			T* GetSystem()
			{
				std::string type_name = typeid(T).name();
				assert(m_systems.find(type_name) != m_systems.end() && "System used before registered.");

				return static_cast<T*>(m_systems[type_name]);
			}

			/**
			 * Erases a destroyed entity from all system lists.
			 *
			 * @param entity The ID of the entity that was destroyed.
			 */
			void EntityDestroyed(Entity entity);

			/**
			 * Notifies each system that an entity's signature has changed.
			 *
			 * @param entity The ID of the entity whose signature has changed.
			 * @param entity_signature The new signature of the entity.
			 *
			 * This function iterates over each system and checks if the entity's new signature matches the system's signature.
			 * If it does, the entity is added to the system's set of entities. If it does not, the entity is removed from the system's set of entities.
			 */
			void EntitySignatureChanged(Entity entity, Signature entity_signature);

			/**
			 * @brief Iterates all systems and calls specific game loop method
			 * 
			 * @param state Current game loop state
			 */
			void IterateSystems(GameLoopState state);
			void IterateSystems(SDL_Event& event);

		private:
			std::shared_ptr<LoggingManager> m_logging_manager;

			// Map from system type name to a signature
			std::unordered_map<std::string, Signature> m_signatures;

			// Map from system type name to a system pointer
			std::unordered_map<std::string, System*> m_systems;
	};
}