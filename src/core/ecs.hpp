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
}

struct System : Object {
    Core::CoreManager& _coreManager;

    System(Core::CoreManager& coreManager)
        : _coreManager(coreManager) {};

    virtual ~System() = default;

    virtual void OnInit() {};
    virtual void OnPreEvent() {};
    virtual void OnEvent(SDL_Event& event) {};
    virtual void OnUpdate(float deltaTime) {};
    virtual void OnRender(SDL_Renderer* renderer, SDL_Window* window, SDL_Surface* surface) {};
    virtual void OnPostRender() {};
    
    std::set<Entity> _entities;
};

enum class GameLoopState {
    OnInit,
    OnPreEvent,
    OnEvent,
    OnUpdate,
    OnRender,
    OnPostRender
};