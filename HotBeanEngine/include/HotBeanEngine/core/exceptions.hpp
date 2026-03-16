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
        ComponentNotRegisteredException() : std::runtime_error("Component not registered") {}

        ComponentNotRegisteredException(std::string_view component_name)
            : std::runtime_error(std::string("Component not registered: ") + std::string(component_name)) {}
    };

    class ComponentNameNotDefinedException : public std::runtime_error {
    public:
        ComponentNameNotDefinedException() : std::runtime_error("Component GetName() method is not defined or empty") {}
    };

    class MaxNumberOfComponentsRegisteredException : public std::length_error {
    public:
        MaxNumberOfComponentsRegisteredException()
            : std::length_error("Maximum number of registered component types reached") {}
    };

    class SystemNotRegisteredException : public std::runtime_error {
    public:
        SystemNotRegisteredException(std::string_view system_name)
            : std::runtime_error(std::string("System not registered: ") + std::string(system_name)) {}
    };
} // namespace HBE::Core