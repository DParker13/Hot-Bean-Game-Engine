#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Position.h"
#include "EventSystem.h"

class GameObject : public EventSystem, public Position<float> {
private:

public:
    GameObject(Position<float> pos);
    GameObject();
};
#endif // GAME_OBJECT_H