#include "brick.h"

Brick::Brick()
{
    img.load("images/brick_1.png");

    width = img.width();
    height = img.height();

    coordX = 10;
    coordY = 30;

    visible = true;
}
