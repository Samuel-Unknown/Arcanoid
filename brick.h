#ifndef BRICK_H
#define BRICK_H

#include "gameobject.h"

class Brick : public GameObject
{
public:
    Brick();

    bool visible; // истина если блок не разрушен
};

#endif // BRICK_H
