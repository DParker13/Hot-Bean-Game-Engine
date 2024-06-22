#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"

class Camera : public GameObject {
public:
    Camera(Position<float> pos);
    Camera();

    void OnUpdate() override;
    void OnRender(SDL_Surface* surface, SDL_Renderer* renderer) override;

};
#endif // CAMERA_H