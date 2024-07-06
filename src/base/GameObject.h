#pragma once

#include <memory>
#include <vector>
#include "Position.h"
#include "EventSystem.h"

class GameObject : public EventSystem, public std::enable_shared_from_this<GameObject> {
public:
    // Default constructor
    GameObject();

    // Constructor taking a starting position
    GameObject(Position<float> startingPos);

    // Event: OnInitialize
    virtual void OnInitialize() {
    
    }

    // Getter for position
    virtual Position<float> GetPosition() const;
    // Setter for position
    virtual void UpdateLocalPosition(Position<float> pos);
    void SetParent(std::shared_ptr<GameObject> newParent);
protected:
    //Parent of this GameObject
    //This GameObject's position is offset by this object's parent worldPosition
    //Changing the localPosition will move this GameObject relative to it's parent position
    std::weak_ptr<GameObject> parent;

    //Children of this GameObject
    //Child positions are offset by this object's worldPosition
    std::vector<std::unique_ptr<GameObject>> children;

    //Position of this GameObject outside of it's parent's Position
    std::unique_ptr<Position<float>> worldPosition;

    //If this object is a child of another GameObject, this position will be offset from the world position
    std::unique_ptr<Position<float>> localPosition;
};
