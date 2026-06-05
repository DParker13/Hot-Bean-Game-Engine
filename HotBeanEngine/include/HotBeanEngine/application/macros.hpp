#pragma once

#include <tuple>

// TODO: Allow setting up systems with components or archetypes
// #define MAKE_SHARED_ARCHETYPE(...) std::make_shared<__VA_ARGS__>().get()

// #define SETUP_SYSTEM_ARCHETYPES(System, ...) \
//     App::GetInstance().GetECSManager()->SetSignature<System>(MAKE_SHARED_ARCHETYPE(__VA_ARGS__));

// #define EXTEND_SYSTEM_ARCHETYPES(OriginalSystem, System, ...)                   \
//     App::GetInstance().GetECSManager()->UnregisterSystem<OriginalSystem>();     \
//     SETUP_SYSTEM_ARCHETYPES(System, __VA_ARGS__)

/**
 * @def g_app
 * @brief Global macro for accessing the singleton Application instance.
 * @see HBE::Application::Application::GetInstance()
 */
#define g_app HBE::Application::Application::GetInstance()

/**
 * @def g_ecs
 * @brief Global macro for accessing the ECS manager from the Application instance.
 * @see HBE::Application::Application::GetECSManager()
 */
#define g_ecs g_app.GetECSManager()

/**
 * @def LOG
 * @brief Macro for logging messages with file, line, and function context.
 * @param type The logging type (e.g., LoggingType::INFO, LoggingType::ERROR).
 * @param message The message to log.
 * @see HBE::Application::Application::Log()
 */
#define LOG(type, message) g_app.Log(type, message, __FILE__, __LINE__, __func__)
