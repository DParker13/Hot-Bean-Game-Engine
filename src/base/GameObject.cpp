#include "GameObject.h"

// Default constructor
GameObject::GameObject()
    : parent(),
      children(),
      worldPosition(std::make_unique<Position<float>>()),
      localPosition(std::make_unique<Position<float>>()) {
}

// Constructor taking a starting position
GameObject::GameObject(Position<float> startingPos)
    : parent(),
      children(),
      worldPosition(std::make_unique<Position<float>>(startingPos)),
      localPosition(std::make_unique<Position<float>>(startingPos)) {
}

// Getter for position
Position<float> GameObject::GetPosition() const {
    return *worldPosition; // Assuming Position<float> has a copy constructor
}

// Setter for position
void GameObject::UpdateLocalPosition(Position<float> pos) {
    localPosition->SetPosition(pos);

    std::shared_ptr<GameObject> parentPtr = parent.lock();
    if (parentPtr != nullptr) {
        // If there is a parent, calculate worldPosition based on parent's worldPosition
        Position<float> parentPos = parentPtr->GetPosition();
        parentPos.Add(*localPosition);

        worldPosition->SetPosition(parentPos);
    }
    else {
        worldPosition->SetPosition(*localPosition);
    }

    for (auto& child : children) {
        child->UpdateLocalPosition(child->GetPosition());
    }
}

void GameObject::SetParent(std::shared_ptr<GameObject> newParent) {
    parent = newParent;
    UpdateLocalPosition(newParent->GetPosition());
}