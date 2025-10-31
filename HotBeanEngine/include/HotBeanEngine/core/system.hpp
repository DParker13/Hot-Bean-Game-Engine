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

#include <HotBeanEngine/core/iname.hpp>
#include <HotBeanEngine/core/entity.hpp>
#include <HotBeanEngine/core/igame_loop.hpp>

namespace HBE::Core {
    /**
     * @brief Base class for systems that process entities with specific components.
     * Systems operate on entities matching their signature.
     * Handles game logic updates and event processing.
     */
    struct System : public IGameLoop, public IName {
        std::set<Entity> m_entities;

        System() = default;
        ~System() = default;

        // System interface
        virtual std::string_view GetName() const = 0;
        virtual void SetSignature() = 0;
        virtual void OnEntityRemoved(Entity entity) {};
        virtual void OnEntityAdded(Entity entity) {};

        // GameLoop interface
        virtual void OnStart() {};
        virtual void OnPreEvent() {};
        virtual void OnEvent(SDL_Event& event) {};
        virtual void OnWindowResize(SDL_Event& event) {};
        virtual void OnFixedUpdate() {};
        virtual void OnUpdate() {};
        virtual void OnRender() {};
        virtual void OnPostRender() {};
    };
}