/**
 * @file ecs.hpp
 * @author Daniel Parker (DParker13)
 * @brief Entity-Component-System structural foundation.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include <SDL_stdinc.h>
#include <SDL.h>
#include <bitset>
#include <set>
#include <sstream>

// Defining entity and component types
using EntityType = Uint32;
using ComponentType = Uint32;

// Entity is an unsigned 32-bit integer
// This is used to identify an entity
using Entity = EntityType;
const Entity MAX_ENTITIES = 5000;

// Component is an unsigned 32-bit integer
// This is used to identify a component
const ComponentType MAX_COMPONENTS = 32;

// Bitset indicates which components an entity has
using Signature = std::bitset<MAX_COMPONENTS>;

struct IGameLoop {
    virtual void OnInit() = 0;
    virtual void OnPreEvent() = 0;
    virtual void OnEvent(SDL_Event& event) = 0;
    virtual void OnUpdate(SDL_Renderer* renderer, float deltaTime) = 0;
    virtual void OnRender(SDL_Renderer* renderer, SDL_Window* window, SDL_Surface* surface) = 0;
    virtual void OnPostRender(SDL_Renderer* renderer) = 0;
};

struct Object {
    virtual ~Object() = default;
    virtual std::string ToString() const = 0;
};

struct ISparseSet : Object {
    virtual ~ISparseSet() = default;
    virtual void Remove(size_t index) = 0;
    virtual size_t Size() const = 0;
};

// Forward declaration of Core::CoreManager for System struct
namespace Core {
    class CoreManager;
};

struct System : public Object, public IGameLoop {
    //public:
    Core::CoreManager& _coreManager;
    std::set<Entity> _entities;

    System(Core::CoreManager& coreManager)
        : _coreManager(coreManager) {};

    virtual ~System() = default;

    // IGameLoop interface
    virtual void OnInit() {};
    virtual void OnPreEvent() {};
    virtual void OnEvent(SDL_Event& event) {};
    virtual void OnUpdate(SDL_Renderer* renderer, float deltaTime) {};
    virtual void OnRender(SDL_Renderer* renderer, SDL_Window* window, SDL_Surface* surface) {};
    virtual void OnPostRender(SDL_Renderer* renderer) {};
};

struct Component : Object {
    Component() = default;
    virtual ~Component() = default;
};

enum class GameLoopState {
    OnInit,
    OnPreEvent,
    OnEvent,
    OnUpdate,
    OnRender,
    OnPostRender
};