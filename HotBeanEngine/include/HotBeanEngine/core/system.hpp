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

#include <HotBeanEngine/core/component.hpp>
#include <HotBeanEngine/core/entity.hpp>
#include <HotBeanEngine/core/igame_loop.hpp>
#include <HotBeanEngine/core/iname.hpp>

namespace HBE::Core {
    /**
     * @brief Base class for systems that process entities with specific components.
     * Systems operate on entities matching their signature.
     * Handles game logic updates and event processing.
     */
    struct SystemBase : public IGameLoop, public IName {
        std::set<EntityID> m_entities;

        virtual ~SystemBase() = default;

        virtual std::string_view GetName() const = 0;
        virtual void OnEntityRemoved(EntityID entity) {};
        virtual void OnEntityAdded(EntityID entity) {};

        // GameLoop
        virtual void OnStart() {};
        virtual void OnPreEvent() {};
        virtual void OnEvent(SDL_Event &event) {};
        virtual void OnWindowResize(SDL_Event &event) {};
        virtual void OnFixedUpdate() {};
        virtual void OnUpdate() {};
        virtual void OnRender() {};
        virtual void OnPostRender() {};
    };

    template <typename... Components>
    struct GameSystem : public SystemBase {
        // GameSystem is a helper class that automatically sets signature from template params
        virtual std::vector<std::string_view> GetRequiredComponents() const final {
            std::vector<std::string_view> required_components;
            (..., required_components.push_back(Components::StaticGetName()));

            return required_components;
        }
    };
} // namespace HBE::Core