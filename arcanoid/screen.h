#ifndef SCREEN_H
#define SCREEN_H

#include "gameobject.h"

class Screen : public GameObject
{
public:
    Screen();
    int FPS;    // Число кадров в секунду
};

#endif // SCREEN_H
