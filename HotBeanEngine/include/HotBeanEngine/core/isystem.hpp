/**
 * @file system.hpp
 * @author Daniel Parker (DParker13)
 * @brief System base class for ECS architecture.
 * @version 0.1
 * @date 2025-02-23
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <set>
#include <tuple>

#include <HotBeanEngine/core/entity.hpp>
#include <HotBeanEngine/core/igame_loop.hpp>
#include <HotBeanEngine/core/iname.hpp>

// Helper macro for declaring required components
#define REQUIRES_COMPONENTS(...) using RequiredComponents = std::tuple<__VA_ARGS__>

namespace HBE::Core {
    /**
     * @brief Base class for systems that process entities with specific components.
     * Systems operate on entities matching their signature.
     * Handles game logic updates and event processing.
     */
    struct ISystem : public IGameLoop, public IName {
        std::set<EntityID> m_entities;

        // System interface
        virtual std::string_view GetName() const = 0;
        virtual void SetSignature() {}; // Optional override - manager extracts from RequiredComponents
        virtual void OnEntityRemoved(EntityID entity) {};
        virtual void OnEntityAdded(EntityID entity) {};

        // GameLoop interface
        virtual void OnStart() {};
        virtual void OnPreEvent() {};
        virtual void OnEvent(SDL_Event &event) {};
        virtual void OnWindowResize(SDL_Event &event) {};
        virtual void OnFixedUpdate() {};
        virtual void OnUpdate() {};
        virtual void OnRender() {};
        virtual void OnPostRender() {};
    };
} // namespace HBE::Core