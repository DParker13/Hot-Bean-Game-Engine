#pragma once

#include <unordered_map>
#include <memory>
#include <iostream>
#include <cassert>

#include "ecs.hpp"

namespace Core {
	class SystemManager {
		public:
			SystemManager();
			~SystemManager();

			void Print() const;
			
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
			std::shared_ptr<T> RegisterSystem()
			{
				std::string typeName = typeid(T).name();

				assert(_systems.find(typeName) == _systems.end() && "Registering system more than once.");

				// Create a pointer to the system and return it so it can be used externally
				auto system = std::make_shared<T>();
				_systems.insert({typeName, system});
				return system;
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
			void SetSignature(Signature signature)
			{
				std::string typeName = typeid(T).name();

				assert(_systems.find(typeName) != _systems.end() && "System used before registered.");

				// Set the signature for this system
				_signatures.insert({typeName, signature});
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
			std::shared_ptr<T> GetSystem()
			{
				std::string typeName = typeid(T).name();

				assert(_systems.find(typeName) != _systems.end() && "System used before registered.");

				return std::static_pointer_cast<T>(_systems[typeName]);
			}

			/**
			 * Erases a destroyed entity from all system lists.
			 *
			 * @param entity The ID of the entity that was destroyed.
			 */
			void EntityDestroyed(Entity entity)
			{
				// Erase a destroyed entity from all system lists
				// _entities is a set so no check needed
				for (auto& [typeName, system] : _systems) {
					system->_entities.erase(entity);
				}
			}

			/**
			 * Notifies each system that an entity's signature has changed.
			 *
			 * @param entity The ID of the entity whose signature has changed.
			 * @param entitySignature The new signature of the entity.
			 *
			 * This function iterates over each system and checks if the entity's new signature matches the system's signature.
			 * If it does, the entity is added to the system's set of entities. If it does not, the entity is removed from the system's set of entities.
			 */
			void EntitySignatureChanged(Entity entity, Signature entitySignature)
			{
				// Notify each system that an entity's signature changed
				for (auto& [typeName, system] : _systems) {
					auto const& systemSignature = _signatures[typeName];

					// Entity signature matches system signature - insert into set
					if ((entitySignature & systemSignature) == systemSignature) {
						system->_entities.insert(entity);
					}
					// Entity signature does not match system signature - erase from set
					else {
						system->_entities.erase(entity);
					}
				}
			}

		private:
			// Map from system type name to a signature
			std::unordered_map<std::string, Signature> _signatures;

			// Map from system type name to a system pointer
			std::unordered_map<std::string, std::shared_ptr<System>> _systems;
	};	
}