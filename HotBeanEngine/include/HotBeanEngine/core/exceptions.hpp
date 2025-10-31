/**
 * @file exceptions.hpp
 * @author Daniel Parker (DParker13)
 * @brief Defines custom exceptions.
 * @version 0.1
 * @date 2025-07-30
 * 
 * @copyright Copyright (c) 2025
 */

#pragma once

namespace HBE::Core {
    struct ComponentNotRegisteredException : public std::runtime_error {
        public:
            ComponentNotRegisteredException()
                : std::runtime_error("Component not registered") {}

            ComponentNotRegisteredException(const std::string& component_name)
                : std::runtime_error("Component not registered: " + component_name) {}
    };

    class ComponentNameNotDefinedException : public std::runtime_error {
        public:
            ComponentNameNotDefinedException()
                : std::runtime_error("Component GetName() method is not defined or empty") {}
    };

    class MaxNumberOfComponentsRegisteredException : public std::length_error {
        public:
            MaxNumberOfComponentsRegisteredException()
                : std::length_error("Maximum number of registered component types reached") {}
    };

    class SystemNotRegisteredException : public std::runtime_error {
        public:
            SystemNotRegisteredException(const std::string& system_name)
                : std::runtime_error("System not registered: " + system_name) {}
    };
}