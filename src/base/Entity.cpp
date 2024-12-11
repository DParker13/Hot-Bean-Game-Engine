#include "Entity.h"

// Default constructor
Entity::Entity()
    : parent(),
      children(),
      worldPosition(std::make_unique<Position<float>>()),
      localPosition(std::make_unique<Position<float>>()) {
}

// Constructor taking a starting position
Entity::Entity(Position<float> startingPos)
    : parent(),
      children(),
      worldPosition(std::make_unique<Position<float>>(startingPos)),
      localPosition(std::make_unique<Position<float>>(startingPos)) {
}

void Entity::OnInitialize() {
    if(children.size() > 0) {
        for (auto& child : children) {
            child->OnInitialize();
        }
    }
}

void Entity::OnUpdate(std::shared_ptr<float> deltaTime) {
    if(children.size() > 0) {
        for (auto& child : children) {
            child->OnUpdate(deltaTime);
        }
    }
}

void Entity::OnRender(SDL_Surface* surface, SDL_Renderer* renderer) {
    if(children.size() > 0) {
        for (auto& child : children) {
            child->OnRender(surface, renderer);
        }
    }
}

// Getter for world position
Position<float> Entity::GetPosition() const {
    return *worldPosition;
}

//Setter for position
void Entity::SetPosition(Position<float> newPos) {
    localPosition->SetPosition(newPos);

    UpdatePositionInWorldSpace();
}

// Setter for world position
void Entity::UpdatePositionInWorldSpace() {
    if (parent != nullptr) {
        // If there is a parent, calculate worldPosition based on parent's worldPosition
        Position<float> parentPos = parent->GetPosition();
        parentPos.Add(*localPosition);

        worldPosition->SetPosition(parentPos);
    }
    else {
        worldPosition->SetPosition(*localPosition);
    }

    for (auto& child : children) {
        child->UpdatePositionInWorldSpace();
    }
}

void Entity::SetParent(std::shared_ptr<Entity> newParent) {
    parent = newParent;
    parent->AddChild(shared_from_this());

    UpdatePositionInWorldSpace();
}

void Entity::AddChild(std::shared_ptr<Entity> newChild) {
    children.push_back(newChild);

    newChild->parent = shared_from_this();
    newChild->UpdatePositionInWorldSpace();
}