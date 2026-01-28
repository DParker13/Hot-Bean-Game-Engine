#pragma once

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

/**
 * @def DEFINE_SIGNATURE
 * @brief Macro to define the signature of a system for ECS registration.
 * @param System The system type.
 * @param Name The system's display name.
 * @param ... Component types that make up the system's signature.
 * @details This macro defines a SetSignature() override for the system, registering its required components.
 */
#define DEFINE_SIGNATURE(System, Name, ...)                                                                            \
    DEFINE_NAME(Name)                                                                                                  \
    void SetSignature() override { g_ecs.SetSignature<System, ##__VA_ARGS__>(); }

/**
 * @def EXTEND_SYSTEM
 * @brief Macro to extend an existing system's signature and unregister the original system.
 * @param OriginalSystem The system to be replaced.
 * @param System The new system type.
 * @param Name The new system's display name.
 * @param ... Component types for the new system's signature.
 * @details This macro unregisters the original system and registers the new system with the specified signature.
 */
#define EXTEND_SYSTEM(OriginalSystem, System, Name, ...)                                                               \
    DEFINE_NAME(Name)                                                                                                  \
    void SetSignature() override {                                                                                     \
        g_ecs.UnregisterSystem<OriginalSystem>();                                                                      \
        g_ecs.SetSignature<System, ##__VA_ARGS__>();                                                                   \
    }
