#pragma once

#include <SDL_stdinc.h>
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

struct IObject {
    virtual ~IObject() = default;
    virtual std::string ToString() const = 0;
};

struct ISparseSet : IObject {
    virtual ~ISparseSet() = default;
    virtual void Remove(size_t index) = 0;
    virtual size_t Size() const = 0;
};

struct System : IObject {
    System() = default;
    virtual ~System() = default;
    
    std::set<Entity> _entities;
};