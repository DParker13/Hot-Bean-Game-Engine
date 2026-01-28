/**
 * @file system_manager.hpp
 * @author Daniel Parker (DParker13)
 * @brief Manages component-system relationship.
 *
 * @version 0.1
 * @date 2025-02-23
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <map>

#include <HotBeanEngine/application/managers/logging_manager.hpp>

namespace HBE::Application::Managers {
    using namespace HBE::Core;

    /**
     * @brief Manages systems that manipulate component data.
     * Handles system registration, execution order, and entity-system matching.
     * Controls system lifecycle and signature-based entity filtering.
     */
    class SystemManager {
    private:
        std::shared_ptr<LoggingManager> m_logging_manager;

        // Map from system type name to a signature
        std::unordered_map<std::string, Signature> m_signatures;

        // Map from system type name to a system pointer
        std::map<std::string, ISystem *> m_systems;
        std::vector<ISystem *> m_systems_ordered;

    public:
        SystemManager(std::shared_ptr<LoggingManager> logging_manager);
        /**
         * @brief Destructor. Releases all registered systems.
         */
        ~SystemManager();

        /**
         * @brief Creates and registers a system with the System Manager
         *
         * @tparam T Type of system
         * @tparam Args Parameter types needed to create system
         * @param params Parameters needed to create system
         * @return T& Reference to newly created system
         */
        template <typename T, typename... Args>
        T &RegisterSystem(Args &&...params) {
            static_assert(std::is_base_of_v<ISystem, T> && "T must inherit from ISystem");

            std::string system_name = std::string(GetSystemName<T>());
            LOG_CORE(LoggingType::DEBUG, "Creating and registering System \"" + system_name + "\"");

            if (IsSystemRegistered<T>()) {
                LOG_CORE(LoggingType::WARNING, "Registering system more than once! Ignoring...");
                return *static_cast<T *>(m_systems[system_name]);
            }

            T *system = new T(std::forward<Args>(params)...);

            // Create a pointer to the system and return it so it can be used externally
            m_systems.insert({system_name, system});
            m_systems_ordered.push_back(system);

            return *system;
        }

        /**
         * Creates and registers a system with the System Manager.
         *
         * @tparam T The type of system to be registered.
         * @return A shared pointer to the system.
         */
        template <typename T>
        T &RegisterSystem() {
            static_assert(std::is_base_of_v<ISystem, T> && "T must inherit from ISystem");

            std::string system_name = std::string(GetSystemName<T>());
            LOG_CORE(LoggingType::DEBUG, "Creating and registering System \"" + system_name + "\"");

            if (IsSystemRegistered<T>()) {
                LOG_CORE(LoggingType::WARNING, "Registering system more than once! Ignoring...");
                return *static_cast<T *>(m_systems[system_name]);
            }

            T *system = new T();

            // Create a pointer to the system and return it so it can be used externally
            m_systems.insert({system_name, system});
            m_systems_ordered.push_back(system);

            return *system;
        }

        /**
         * @brief Unregister the system from the ECS Manager
         *
         * @tparam T Type of system
         */
        template <typename T>
        void UnregisterSystem() {
            std::string system_name = std::string(GetSystemName<T>());
            LOG_CORE(LoggingType::DEBUG, "Unregistering System \"" + system_name + "\"");

            if (!IsSystemRegistered<T>()) {
                LOG_CORE(LoggingType::WARNING, "System is not registered");
                return;
            }

            T *system = GetSystem<T>();

            RemoveSignature<T>();

            // TODO: Can this be done better?
            // Remove system from ordered list
            m_systems_ordered.erase(
                std::remove(m_systems_ordered.begin(), m_systems_ordered.end(), m_systems[system_name]),
                m_systems_ordered.end());
            m_systems.erase(system_name);

            delete system;
        }

        void UnregisterSystem(ISystem *system);

        template <typename T>
        bool IsSystemRegistered() {
            return m_systems.find(std::string(GetSystemName<T>())) != m_systems.end();
        }

        /**
         * Sets the signature for a system that has already been registered.
         *
         * @tparam T The type of system to be registered.
         * @param signature The signature for the system.
         * @throws assertion failure if the system type has not been registered.
         */
        template <typename T>
        void SetSignature(Signature signature) {
            if (!IsSystemRegistered<T>()) {
                LOG_CORE(LoggingType::WARNING, "System is not registered");
                return;
            }

            std::string system_name = std::string(GetSystemName<T>());

            LOG_CORE(LoggingType::DEBUG, "System \"" + system_name +
                                             "\" Signature set to"
                                             " \"" +
                                             signature.to_string() + "\"");

            // Set the signature for this system
            m_signatures.insert({system_name, signature});
        }

        /**
         * @brief Get the Signature of a System type T
         *
         * @tparam T Type of System
         * @return const Signature& Reference to the System's Signature
         */
        template <typename T>
        Signature &GetSignature() {
            if (!IsSystemRegistered<T>()) {
                LOG_CORE(LoggingType::ERROR, "System is not registered");
                throw std::runtime_error("System is not registered");
            }

            // Get the signature for this system
            return m_signatures[std::string(GetSystemName<T>())];
        }

        /**
         * @brief Get the System
         *
         * @tparam T Type of System
         * @return T* Pointer to the registered System
         */
        template <typename T>
        T *GetSystem() {
            if (!IsSystemRegistered<T>()) {
                LOG_CORE(LoggingType::WARNING, "System is not registered");
                return nullptr;
            } else {
                return static_cast<T *>(m_systems[std::string(GetSystemName<T>())]);
            }
        }

        /**
         * Erases a destroyed entity from all system lists.
         *
         * @param entity The ID of the entity that was destroyed.
         */
        void EntityDestroyed(EntityID entity);

        /**
         * Notifies each system that an entity's signature has changed.
         *
         * @param entity The ID of the entity whose signature has changed.
         * @param entity_signature The new signature of the entity.
         *
         * This function iterates over each system and checks if the entity's new signature matches the system's
         * signature. If it does, the entity is added to the system's set of entities. If it does not, the entity is
         * removed from the system's set of entities.
         */
        void EntitySignatureChanged(EntityID entity, Signature entity_signature);

        /**
         * @brief Iterates all systems and calls specific game loop method
         *
         * @param state Current game loop state
         */
        void IterateSystems(GameLoopState state);

        /**
         * @brief Iterates all systems and calls specific game loop event methods
         *
         * @param event SDL event
         * @param state Current game loop state
         */
        void IterateSystems(SDL_Event &event, GameLoopState state);

        /**
         * @brief Retrieve all registered systems in execution order.
         * @return Vector of system pointers.
         */
        std::vector<ISystem *> GetAllSystems();

    private:
        bool IsSystemRegistered(ISystem *system);

        template <typename T>
        void RemoveSignature() {
            if (!IsSystemRegistered<T>()) {
                LOG_CORE(LoggingType::WARNING, "System is not registered");
                return;
            }

            std::string system_name = std::string(GetSystemName<T>());

            LOG_CORE(LoggingType::DEBUG, "System \"" + system_name + "\" Signature removed");

            m_signatures.erase(system_name);
        }

        void RemoveSignature(ISystem *system);

        /**
         * @brief Retrieves the name of the component
         *
         * @tparam T The type of component
         * @return std::string The name of the component
         * @throw ComponentNameNotDefinedException
         */
        template <typename T>
        std::string_view GetSystemName() const {
            static_assert(std::is_base_of_v<ISystem, T>, "T must inherit from ISystem");
            static_assert(has_static_get_name<T>::value, "T must have a StaticGetName() function");

            if (T::StaticGetName().empty()) {
                LOG_CORE(LoggingType::WARNING, "System name is empty");
            }

            return T::StaticGetName();
        }
    };
} // namespace HBE::Application::Managers