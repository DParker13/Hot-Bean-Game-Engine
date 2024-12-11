#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include "Position.h"
#include "EventSystem.h"

class Entity : public EventSystem, public std::enable_shared_from_this<Entity> {
public:
    // Default constructor
    Entity();

    // Constructor taking a starting position
    Entity(Position<float> startingPos);

    // Event: OnInitialize
    virtual void OnInitialize();

    //EventSystem methods
    void OnUpdate(std::shared_ptr<float> deltaTime) override;
    void OnRender(SDL_Surface* surface, SDL_Renderer* renderer) override;

    // Getter for position
    virtual Position<float> GetPosition() const;
    // Setter for position
    virtual void SetPosition(Position<float> newPos);

    void UpdatePositionInWorldSpace();
    void SetParent(std::shared_ptr<Entity> newParent);
    void AddChild(std::shared_ptr<Entity> newChild);

protected:
    //Parent of this Entity
    //This Entity's position is offset by this object's parent worldPosition
    //Changing the localPosition will move this Entity relative to it's parent position
    std::shared_ptr<Entity> parent;

    //Children of this Entity
    //Child positions are offset by this object's worldPosition
    std::vector<std::shared_ptr<Entity>> children;

    //Position of this Entity outside of it's parent's Position
    std::unique_ptr<Position<float>> worldPosition;

    //If this object is a child of another Entity, this position will be offset from the world position
    std::unique_ptr<Position<float>> localPosition;
};
